#ifndef CPP_OTP_BIRTHDAY_H
#define CPP_OTP_BIRTHDAY_H

#include "Today.h"

class Birthday {

public:
    Birthday(Today& today);
    bool IsBirthday();

private:
    Today& today;
};


#endif //CPP_OTP_BIRTHDAY_H
