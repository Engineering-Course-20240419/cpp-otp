#include "CppUTest/TestHarness.h"
#include "Birthday.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(Birthday) {

};

TEST(Birthday, IsBirthday) {
    Birthday target;

    bool actual = target.IsBirthday();

    CHECK_TRUE(actual);
}
