#include <iostream>
#include "Birthday.h"
#include "AuthenticationService.h"

int main() {
    Birthday birthday;
    std::cout << "is birthday: " << birthday.IsBirthday() << std::endl;
    return 0;
}
