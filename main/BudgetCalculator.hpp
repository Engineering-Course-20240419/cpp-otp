#include <ctime>
#include "IBudgetDB.hpp"

class BudgetCalculator {

public:
  BudgetCalculator(IBudgetDB &budgetDB);

  uint32_t query(const tm& start, const tm& end);

private:
  struct BudgetRange {
    std::vector<IBudgetDB::Budget>::const_iterator start;
    std::vector<IBudgetDB::Budget>::const_iterator end;
  };
  static uint32_t calculateMonthAverage(IBudgetDB::Budget const &budget);
  static uint32_t calculateDaysBetweenDate(const tm& start, const tm& end);
  static BudgetRange filterBudgetList(std::vector<IBudgetDB::Budget> const &allBudget, const tm& start, const tm& end);
  static tm getLastDayOfMonth(const tm& date);
  static tm getFirstDayOfMonth(const tm& date);
  bool isAfter(const tm& tm1, const tm& tm2);
  static bool isAfterOrSame(const tm& tm1, const tm& tm2);
  bool isBefore(const tm &tm1, const tm &tm2);
  static bool isBeforeOrSame(const tm& tm1, const tm& tm2);
  IBudgetDB &budgetDB_;

};
