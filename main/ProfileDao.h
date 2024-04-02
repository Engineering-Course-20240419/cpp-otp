#ifndef CPP_OTP_PROFILEDAO_H
#define CPP_OTP_PROFILEDAO_H

#include <string>
#include <map>

class ProfileDao {

public:
    ProfileDao();
    std::string getPassword(std::string userName);

private:
    std::map<std::string, std::string> profiles;
};

#endif //CPP_OTP_PROFILEDAO_H
