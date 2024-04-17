#include "ProfileDao.h"

ProfileDao::ProfileDao() {
    profiles["joey"] = "91";
    profiles["mei"] = "99";
}

std::string ProfileDao::getPassword(const std::string userName) {
    return profiles[userName];
}

ProfileDao::~ProfileDao() {}
