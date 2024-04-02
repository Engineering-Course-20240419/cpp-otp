#include <iostream>
#include <iomanip>
#include <sstream>
#include "RsaTokenDao.h"
#include <ctime>

using namespace std;

std::string RsaTokenDao::getRandom(const std::string userName) {
    srand((unsigned)time(NULL));
    ostringstream oss;
    oss << setw(6) << setfill('0') << rand() % 1000000;
    std::string result = oss.str();
    cout << "randomCode:" << result << endl;

    return result;
}
