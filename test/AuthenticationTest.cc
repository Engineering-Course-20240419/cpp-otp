#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "AuthenticationService.h"

TEST_GROUP(AuthenticationService) {
    void teardown() {
        mock().clear();
    }
};

//class StubProfileDao : public ProfileDao {
//public:
//    std::string getPassword(std::string userName) {
//        return password;
//    }
//    std::string password;
//};

class StubProfileDao : public ProfileDao {
public:
    std::string getPassword(std::string userName) {
        return mock().actualCall("getPassword").returnStringValue();
    }
};

//class StubRsaTokenDao : public RsaTokenDao {
//public:
//    std::string getRandom(std::string userName) {
//        return token;
//    }
//    std::string token;
//};

class StubRsaTokenDao : public RsaTokenDao {
public:
    std::string getRandom(std::string userName) {
        return mock().actualCall("getRandom").returnStringValue();
    }
};

TEST(AuthenticationService, IsValid) {
    StubProfileDao stubProfileDao;
//    stubProfileDao.password = "91";
    mock().expectOneCall("getPassword").andReturnValue("91");
    StubRsaTokenDao stubRsaTokenDao;
//    stubRsaTokenDao.token = "000000";
    mock().expectOneCall("getRandom").andReturnValue("000000");
    Logger logger;
    AuthenticationService target = AuthenticationService(stubProfileDao, stubRsaTokenDao, logger);

    bool actual = target.isValid("joey", "91000000");

    CHECK_TRUE(actual);
}

TEST(AuthenticationService, IsNotValid) {
    StubProfileDao stubProfileDao;
//    stubProfileDao.password = "91";
    mock().expectOneCall("getPassword").andReturnValue("91");
    StubRsaTokenDao stubRsaTokenDao;
//    stubRsaTokenDao.token = "123456";
    mock().expectOneCall("getRandom").andReturnValue("123456");
    Logger logger;
    AuthenticationService target = AuthenticationService(stubProfileDao, stubRsaTokenDao, logger);

    bool actual = target.isValid("joey", "91000000");

    CHECK_FALSE(actual);
}

class MockLogger : public Logger {
public:
    void log(std::string message) {
        _message = message;
    }
    std::string _message;
};

TEST(AuthenticationService, Log) {
    StubProfileDao stubProfileDao;
//    stubProfileDao.password = "91";
    mock().expectOneCall("getPassword").andReturnValue("91");
    StubRsaTokenDao stubRsaTokenDao;
//    stubRsaTokenDao.token = "123456";
    mock().expectOneCall("getRandom").andReturnValue("123456");
    MockLogger mockLogger;
    AuthenticationService target = AuthenticationService(stubProfileDao, stubRsaTokenDao, mockLogger);

    target.isValid("joey", "91000000");

    STRCMP_EQUAL("invalid login: joey", mockLogger._message.c_str());
}
