#include "Today.h"

tm* Today::getToday() {
    time_t currentTime;
    time(&currentTime);
    return localtime(&currentTime);
}
