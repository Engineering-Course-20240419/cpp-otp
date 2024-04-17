//
// Created by Joseph Yao on 2018/7/31.
//

#include <string>
#include "AuthenticationService.h"
#include "ProfileDao.h"
#include "RsaTokenDao.h"

AuthenticationService::AuthenticationService(ProfileDao& profileDao, RsaTokenDao& rsaTokenDao) : profileDao(profileDao), rsaTokenDao(rsaTokenDao) {

}

bool AuthenticationService::isValid(const std::string userName, const std::string password) {
    std::string passwordFromDao = profileDao.getPassword(userName);

    std::string randomCode = rsaTokenDao.getRandom(userName);

    std::string validPassword = passwordFromDao + randomCode;
    bool isValid = password == validPassword;

    if (isValid) {
        return true;
    } else {
        return false;
    }
}
