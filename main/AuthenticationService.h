#ifndef CPP_OTP_AUTHENTICATIONSERVICE_H
#define CPP_OTP_AUTHENTICATIONSERVICE_H

#include <string>
#include "ProfileDao.h"
#include "RsaTokenDao.h"
#include "Logger.h"

class AuthenticationService {

public:
    AuthenticationService(ProfileDao& profileDao, RsaTokenDao& rsaTokenDao, Logger& logger);
    bool isValid(const std::string userName, const std::string password);

private:
    ProfileDao& profileDao;
    RsaTokenDao& rsaTokenDao;
    Logger& logger;
};


#endif //CPP_OTP_AUTHENTICATIONSERVICE_H
