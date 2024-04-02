#include "Birthday.h"
#include <ctime>

bool Birthday::IsBirthday() {
    time_t currentTime;
    time(&currentTime);
    tm* localTime = localtime(&currentTime);

    int currentDay = localTime->tm_mday;
    int currentMonth = localTime->tm_mon + 1;
    return currentDay == 9 && currentMonth == 4;
}
