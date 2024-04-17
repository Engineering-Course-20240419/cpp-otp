#include "Birthday.h"
#include <ctime>

Birthday::Birthday(Today& today) : today(today) {

}

bool Birthday::IsBirthday() {
    tm* localTime = today.getToday();

    int currentDay = localTime->tm_mday;
    int currentMonth = localTime->tm_mon + 1;
    return currentDay == 9 && currentMonth == 4;
}
