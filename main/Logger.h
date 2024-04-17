#ifndef CPP_OTP_FOR_COURSE_LOGGER_H
#define CPP_OTP_FOR_COURSE_LOGGER_H

#include <string>

class Logger {

public:
    virtual void log(std::string message);
    virtual ~Logger() {};
};


#endif //CPP_OTP_FOR_COURSE_LOGGER_H
