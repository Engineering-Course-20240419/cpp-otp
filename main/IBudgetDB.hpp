#pragma once

#include <vector>

class Budget {
public:
    Budget(unsigned short year, unsigned char month, unsigned long money) : budgetMonth_year(year), budgetMonth_month(month), money_(money) {

    }

    tm getFirstDayOfMonth() const;
    unsigned short budgetMonth_year;
    unsigned char budgetMonth_month;
    unsigned long money_;
};

class IBudgetDB {
public:
    virtual std::vector<Budget> findAll() = 0; // fixme std::bad_alloc?
};

tm Budget::getFirstDayOfMonth() const {
    tm firstDay = tm();
    firstDay.tm_year = budgetMonth_year - 1900;
    firstDay.tm_mon = budgetMonth_month - 1;
    firstDay.tm_mday = 1;
    return firstDay;
}
