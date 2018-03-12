#include "to_int.hpp"
#include <iostream>

using namespace gdp::gdu;
using namespace std;

int main() {
    cout << to_int<int>("123") << endl;
    cout << to_int<uint32_t>("1231afdal") << endl;
    cout << to_int<uint64_t>("1234567890123456") << endl;
    uint32_t ret = to_int<uint64_t>("1234567890123456");
//    uint64_t ret = to_int<uint64_t>("1234567890123456");
    cout << ret << endl;
    return 0;
}
