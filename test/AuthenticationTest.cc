#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "AuthenticationService.h"

class StubProfileDao : public ProfileDao {
public:
    std::string getPassword(std::string userName) {
        return mock().actualCall("getPassword").returnStringValue();
    }
};

class StubRsaTokenDao : public RsaTokenDao {
public:
    std::string getRandom(std::string userName) {
        return mock().actualCall("getRandom").returnStringValue();
    }
};

class MockLogger : public Logger {
public:
    void log(std::string message) {
        mock().actualCall("log").withStringParameter("message", message.c_str());
    }
};

TEST_GROUP(AuthenticationService) {
    StubProfileDao stubProfileDao;
    StubRsaTokenDao stubRsaTokenDao;
    MockLogger mockLogger;
    AuthenticationService* target;
    void setup() {
        target = new AuthenticationService(stubProfileDao, stubRsaTokenDao, mockLogger);
        mock().ignoreOtherCalls();
    }
    void teardown() {
        mock().clear();
        delete target;
        target = NULL;
    }
    void givenPassword(const char * password) {
        mock().expectOneCall("getPassword").andReturnValue(password);
    }
    void givenToken(const char * token) {
        mock().expectOneCall("getRandom").andReturnValue(token);
    }
};

TEST(AuthenticationService, IsValid) {
    givenPassword("91");
    givenToken("000000");

    bool actual = target->isValid("joey", "91000000");

    CHECK_TRUE(actual);
}

TEST(AuthenticationService, IsNotValid) {
    givenPassword("91");
    givenToken("123456");

    bool actual = target->isValid("joey", "91000000");

    CHECK_FALSE(actual);
}

TEST(AuthenticationService, Log) {
    givenPassword("91");
    givenToken("123456");
    mock().expectOneCall("log").withStringParameter("message", "invalid login: joey");

    target->isValid("joey", "91000000");

    mock().checkExpectations();
}
