#include "CppUTest/TestHarness.h"
#include "Birthday.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(Birthday) {
    void teardown() {
        mock().clear();
    }
};

//class StubToday : public Today {
//public:
//    tm* getToday() {
//        time_t currentTime;
//        time(&currentTime);
//        tm* today = localtime(&currentTime);
//        today->tm_mon = month - 1;
//        today->tm_mday = day;
//        return today;
//    }
//    int month;
//    int day;
//};

class StubToday : public Today {
public:
    tm* getToday() {
        return (tm*) (mock().actualCall("getToday").returnPointerValue());
    }
};

TEST(Birthday, IsBirthday) {
    StubToday stubToday;
//    stubToday.month = 4;
//    stubToday.day = 9;
    time_t currentTime;
    time(&currentTime);
    tm* today = localtime(&currentTime);
    today->tm_mon = 4 - 1;
    today->tm_mday = 9;
    mock().expectOneCall("getToday").andReturnValue(today);
    Birthday target = Birthday(stubToday);

    bool actual = target.IsBirthday();

    CHECK_TRUE(actual);
}

TEST(Birthday, IsNotBirthday) {
    StubToday stubToday;
//    stubToday.month = 5;
//    stubToday.day = 20;
    time_t currentTime;
    time(&currentTime);
    tm* today = localtime(&currentTime);
    today->tm_mon = 5 - 1;
    today->tm_mday = 20;
    mock().expectOneCall("getToday").andReturnValue(today);
    Birthday target = Birthday(stubToday);

    bool actual = target.IsBirthday();

    CHECK_FALSE(actual);
}
