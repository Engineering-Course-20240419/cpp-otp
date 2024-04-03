#include <ctime>
#include "IBudgetDB.hpp"

class BudgetCalculator {

public:
  BudgetCalculator(IBudgetDB &budgetDB);

  unsigned long query(const tm& start, const tm& end);

private:
  struct BudgetRange {
    std::vector<Budget>::const_iterator start;
    std::vector<Budget>::const_iterator end;
  };
  static unsigned long calculateMonthAverage(Budget const &budget);
  static unsigned long calculateDaysBetweenDate(const tm& start, const tm& end);
  static BudgetRange filterBudgetList(std::vector<Budget> const &allBudget, const tm& start, const tm& end);
  static tm getLastDayOfMonth(const tm& date);
  static tm getFirstDayOfMonth(const tm& date);
  bool isAfter(const tm& tm1, const tm& tm2);
  static bool isAfterOrSame(const tm& tm1, const tm& tm2);
  bool isBefore(const tm &tm1, const tm &tm2);
  static bool isBeforeOrSame(const tm& tm1, const tm& tm2);
  IBudgetDB &budgetDB_;

};
