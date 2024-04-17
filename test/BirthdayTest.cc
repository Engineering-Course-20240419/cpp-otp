#include "CppUTest/TestHarness.h"
#include "Birthday.h"
#include "CppUTestExt/MockSupport.h"

class StubToday : public Today {
public:
    tm* getToday() {
        return (tm*) (mock().actualCall("getToday").returnPointerValue());
    }
};

TEST_GROUP(Birthday) {
    StubToday stubToday;
    Birthday* target;
    void setup() {
        target = new Birthday(stubToday);
    }
    void teardown() {
        mock().clear();
        delete target;
        target = NULL;
    }
    void givenToday(int month, int day) {
        time_t currentTime;
        time(&currentTime);
        tm* today = localtime(&currentTime);
        today->tm_mon = month - 1;
        today->tm_mday = day;
        mock().expectOneCall("getToday").andReturnValue(today);
    }
};

TEST(Birthday, IsBirthday) {
    givenToday(4, 9);

    bool actual = target->IsBirthday();

    CHECK_TRUE(actual);
}

TEST(Birthday, IsNotBirthday) {
    givenToday(5, 20);

    bool actual = target->IsBirthday();

    CHECK_FALSE(actual);
}
