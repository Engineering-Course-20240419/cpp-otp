#pragma once

#include <vector>

class IBudgetDB {
public:
    class Budget {
    public:
        Budget(uint16_t year, uint8_t month, uint32_t money) : budgetMonth_year(year), budgetMonth_month(month), money_(money) {

        }

        tm getFirstDayOfMonth() const;
        uint16_t budgetMonth_year;
        uint8_t budgetMonth_month;
        uint32_t money_;
    };

    virtual std::vector<Budget> findAll() = 0; // fixme std::bad_alloc?
};

tm IBudgetDB::Budget::getFirstDayOfMonth() const {
    tm firstDay = {};
    firstDay.tm_year = budgetMonth_year - 1900;
    firstDay.tm_mon = budgetMonth_month - 1;
    firstDay.tm_mday = 1;
    return firstDay;
}
