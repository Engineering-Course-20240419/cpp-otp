#pragma once

#include <cstdint>
#include <vector>

class IBudgetDB {
public:
    class Budget {
    public:
        Budget(uint16_t year, uint8_t month, uint32_t money) : budgetMonth_year(year), budgetMonth_month(month),
                                                               money_(money) {
        }

        uint16_t budgetMonth_year;
        uint8_t budgetMonth_month;
        uint32_t money_;
    };

    virtual std::vector<Budget> findAll() = 0; // fixme std::bad_alloc?
};