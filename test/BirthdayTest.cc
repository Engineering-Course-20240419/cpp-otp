#include "CppUTest/TestHarness.h"
#include "Birthday.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(Birthday) {

};

class StubToday : public Today {
public:
    tm* getToday() {
        time_t currentTime;
        time(&currentTime);
        tm* today = localtime(&currentTime);
        today->tm_mon = month - 1;
        today->tm_mday = day;
        return today;
    }
    int month;
    int day;
};

TEST(Birthday, IsBirthday) {
    StubToday stubToday;
    stubToday.month = 4;
    stubToday.day = 9;
    Birthday target = Birthday(stubToday);

    bool actual = target.IsBirthday();

    CHECK_TRUE(actual);
}

TEST(Birthday, IsNotBirthday) {
    StubToday stubToday;
    stubToday.month = 5;
    stubToday.day = 20;
    Birthday target = Birthday(stubToday);

    bool actual = target.IsBirthday();

    CHECK_FALSE(actual);
}
