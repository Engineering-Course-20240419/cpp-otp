#include "CppUTest/TestHarness.h"
#include "BudgetCalculator.hpp"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(BudgetCalculator) {

};

tm date(unsigned short year, unsigned char month, unsigned char day) {
    time_t currentTime;
    time(&currentTime);
    tm* date = localtime(&currentTime);
    date->tm_hour = 0;
    date->tm_min = 0;
    date->tm_sec = 0;
    date->tm_year = year - 1900;
    date->tm_mon = month - 1;
    date->tm_mday = day;
    return *date;
}

TEST(BudgetCalculator, xxx) {
}
