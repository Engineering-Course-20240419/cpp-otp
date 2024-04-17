#include <iostream>
#include "Birthday.h"
#include "AuthenticationService.h"

int main() {
    Today today;
    Birthday birthday = Birthday(today);
    std::cout << "is birthday: " << birthday.IsBirthday() << std::endl;
    return 0;
}
