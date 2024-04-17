//
// Created by Joseph Yao on 2018/7/31.
//

#include <string>
#include "AuthenticationService.h"
#include "ProfileDao.h"
#include "RsaTokenDao.h"
#include "Logger.h"

AuthenticationService::AuthenticationService(ProfileDao& profileDao, RsaTokenDao& rsaTokenDao, Logger& logger) : profileDao(profileDao), rsaTokenDao(rsaTokenDao), logger(logger) {

}

bool AuthenticationService::isValid(const std::string userName, const std::string password) {
    std::string passwordFromDao = profileDao.getPassword(userName);

    std::string randomCode = rsaTokenDao.getRandom(userName);

    std::string validPassword = passwordFromDao + randomCode;
    bool isValid = password == validPassword;

    if (isValid) {
        return true;
    } else {
        logger.log("invalid login: " + userName);
        return false;
    }
}
