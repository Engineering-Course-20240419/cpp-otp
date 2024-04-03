#include "BudgetCalculator.hpp"
#include <vector>
#include "IBudgetDB.hpp"

BudgetCalculator::BudgetCalculator(IBudgetDB &budgetDB) : budgetDB_(budgetDB) {
}

bool BudgetCalculator::isAfter(const tm& tm1, const tm& tm2) {
    // Convert tm structures to time_t
    std::time_t time1 = std::mktime(const_cast<std::tm*>(&tm1));
    std::time_t time2 = std::mktime(const_cast<std::tm*>(&tm2));

    // Compare time_t values
    return time1 > time2;
}

bool BudgetCalculator::isAfterOrSame(const tm& tm1, const tm& tm2) {
    // Convert tm structures to time_t
    std::time_t time1 = std::mktime(const_cast<std::tm*>(&tm1));
    std::time_t time2 = std::mktime(const_cast<std::tm*>(&tm2));

    // Compare time_t values
    return time1 >= time2;
}

bool BudgetCalculator::isBefore(const tm& tm1, const tm& tm2) {
    // Convert tm structures to time_t
    std::time_t time1 = std::mktime(const_cast<std::tm*>(&tm1));
    std::time_t time2 = std::mktime(const_cast<std::tm*>(&tm2));

    // Compare time_t values
    return time1 < time2;
}

bool BudgetCalculator::isBeforeOrSame(const tm& tm1, const tm& tm2) {
    // Convert tm structures to time_t
    std::time_t time1 = std::mktime(const_cast<std::tm*>(&tm1));
    std::time_t time2 = std::mktime(const_cast<std::tm*>(&tm2));

    // Compare time_t values
    return time1 <= time2;
}

uint32_t BudgetCalculator::query(const tm& start, const tm& end) {
    if (isAfter(start, end)) {
        return 0;
    }

    std::vector<IBudgetDB::Budget> allBudget = budgetDB_.findAll();

    BudgetRange budgetRange = filterBudgetList(allBudget, start, end);

    if (budgetRange.end == allBudget.end() || budgetRange.start == allBudget.end()) {
        return 0;
    }

    const tm& lastDayOfFoundMonth = getLastDayOfMonth(budgetRange.end->getFirstDayOfMonth());
    const tm& firstDayOfFoundMonth = getFirstDayOfMonth(budgetRange.start->getFirstDayOfMonth());
    const tm& realEnd = isBefore(lastDayOfFoundMonth, end) ? lastDayOfFoundMonth : end;
    const tm& realStart = isAfter(firstDayOfFoundMonth, start) ? firstDayOfFoundMonth : start;

    if (budgetRange.start == budgetRange.end) {
        uint32_t const average = calculateMonthAverage(*budgetRange.start);

        uint32_t const days = calculateDaysBetweenDate(realStart, realEnd);

        return average * days;
    }

    uint32_t const startMonthAverage = calculateMonthAverage(*budgetRange.start);
    const tm& monthEnd = getLastDayOfMonth(budgetRange.start->getFirstDayOfMonth());
    uint32_t const daysInFirstMonth = calculateDaysBetweenDate(realStart, monthEnd);

    uint32_t const budgetFirstMonth = daysInFirstMonth * startMonthAverage;

    std::vector<IBudgetDB::Budget>::const_iterator it = budgetRange.start + 1U;
    uint32_t budgetBetween = 0;
    while (it != budgetRange.end) {
        budgetBetween += it->money_;
        it++;
    }

    uint32_t const endMonthAverage = calculateMonthAverage(*budgetRange.end);
    const tm& monthStart = getFirstDayOfMonth(budgetRange.end->getFirstDayOfMonth());
    uint32_t const daysInLastMonth = calculateDaysBetweenDate(monthStart, realEnd);

    uint32_t const budgetEndMonth = daysInLastMonth * endMonthAverage;

    uint32_t const total = budgetFirstMonth + budgetBetween + budgetEndMonth;

    return total;
}

uint32_t BudgetCalculator::calculateMonthAverage(IBudgetDB::Budget const &budget) {

    const tm& lastDay = getLastDayOfMonth(budget.getFirstDayOfMonth());
    const tm& firstDay = getFirstDayOfMonth(budget.getFirstDayOfMonth());
    uint32_t const days = calculateDaysBetweenDate(firstDay, lastDay);
    return budget.money_ / days;
}

uint32_t BudgetCalculator::calculateDaysBetweenDate(const tm& start,
                                                    const tm& end) {
    // Convert tm structures to time_t
    std::time_t time1 = std::mktime(const_cast<std::tm*>(&end));
    std::time_t time2 = std::mktime(const_cast<std::tm*>(&start));

    // Calculate the difference in seconds
    double seconds = difftime(time1, time2);

    // Convert seconds to days
    return static_cast<uint32_t>(seconds / (60 * 60 * 24));
}

BudgetCalculator::BudgetRange
BudgetCalculator::filterBudgetList(const std::vector<IBudgetDB::Budget> &allBudget, const tm& start,
                                   const tm& end) {
    BudgetRange budgetRange;
    const tm& startMonth = getFirstDayOfMonth(start);
    const tm& endMonth = getFirstDayOfMonth(end);
    budgetRange.start = allBudget.end();
    budgetRange.end = allBudget.end();
    bool foundStart = false;
    std::vector<IBudgetDB::Budget>::const_iterator it = allBudget.begin();
    while (it != allBudget.end()) {
        if ((!foundStart) && (isAfterOrSame(it->getFirstDayOfMonth(), startMonth))) {
            budgetRange.start = it;
            foundStart = true;
        }

        if (isBeforeOrSame(it->getFirstDayOfMonth(), endMonth)) {
            budgetRange.end = it;
        } else {
            break;
        }
        it++;
    }
    return budgetRange;
}

tm BudgetCalculator::getLastDayOfMonth(const tm& date) {
    // Create a copy of the input tm structure to modify
    std::tm lastDayTm = date;

    // Set tm_mday to 0, which is treated as the day before the first day of the month
    lastDayTm.tm_mday = 0;

    // Set tm_mon to the next month (0-11, thus +1 for the next month)
    lastDayTm.tm_mon += 1;

    // Normalize the tm structure to get the last day of the input month
    // mktime adjusts the tm_mday to the last day of the previous month if tm_mday is set to 0
    std::mktime(&lastDayTm);

    // Now, lastDayTm.tm_mday is the last day of the input month
    return lastDayTm;
}

tm BudgetCalculator::getFirstDayOfMonth(const tm& date) {
    // Create a copy of the input tm structure to modify
    std::tm firstDayTm = date;

    // Set tm_mday to 1, which is the first day of the month
    firstDayTm.tm_mday = 1;

    // Normalize the tm structure to get the first day of the input month
    std::mktime(&firstDayTm);

    // Now, firstDayTm.tm_mday is the first day of the input month
    return firstDayTm;
}
