#include "IBudgetDB.hpp"
#include <ctime>

tm Budget::getFirstDayOfMonth() const {
    time_t currentTime;
    time(&currentTime);
    tm* firstDay = localtime(&currentTime);
    firstDay->tm_hour = 0;
    firstDay->tm_min = 0;
    firstDay->tm_sec = 0;
    firstDay->tm_year = budgetMonth_year - 1900;
    firstDay->tm_mon = budgetMonth_month - 1;
    firstDay->tm_mday = 1;
    return *firstDay;
}
