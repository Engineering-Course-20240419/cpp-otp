#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "AuthenticationService.h"

TEST_GROUP(AuthenticationService) {

};

class StubProfileDao : public ProfileDao {
public:
    std::string getPassword(std::string userName) {
        return password;
    }
    std::string password;
};

class StubRsaTokenDao : public RsaTokenDao {
public:
    std::string getRandom(std::string userName) {
        return token;
    }
    std::string token;
};

TEST(AuthenticationService, IsValid) {
    StubProfileDao stubProfileDao;
    stubProfileDao.password = "91";
    StubRsaTokenDao stubRsaTokenDao;
    stubRsaTokenDao.token = "000000";
    AuthenticationService target = AuthenticationService(stubProfileDao, stubRsaTokenDao);

    bool actual = target.isValid("joey", "91000000");

    CHECK_TRUE(actual);
}

TEST(AuthenticationService, IsNotValid) {
    StubProfileDao stubProfileDao;
    stubProfileDao.password = "91";
    StubRsaTokenDao stubRsaTokenDao;
    stubRsaTokenDao.token = "123456";
    AuthenticationService target = AuthenticationService(stubProfileDao, stubRsaTokenDao);

    bool actual = target.isValid("joey", "91000000");

    CHECK_FALSE(actual);
}

