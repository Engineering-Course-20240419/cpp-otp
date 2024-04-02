//
// Created by Joseph Yao on 2018/7/31.
//

#include <string>
#include "AuthenticationService.h"
#include "ProfileDao.h"
#include "RsaTokenDao.h"

bool AuthenticationService::isValid(const std::string userName, const std::string password) {
    ProfileDao profileDao;
    std::string passwordFromDao = profileDao.getPassword(userName);

    RsaTokenDao rsaTokenDao;
    std::string randomCode = rsaTokenDao.getRandom(userName);

    std::string validPassword = passwordFromDao + randomCode;
    bool isValid = password == validPassword;

    if (isValid) {
        return true;
    } else {
        return false;
    }
}
