#ifndef CPP_OTP_BUDGET_H
#define CPP_OTP_BUDGET_H

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
    virtual std::vector<Budget> findAll() = 0;
};

#endif //CPP_OTP_BUDGET_H
