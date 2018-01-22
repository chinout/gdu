#include "hash.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {
    uint32_t mod = 1 << 31;
    std::string str1 = "abc";
    uint32_t hash1 = gdp::gdu::hash_code(str1, mod);
    std::cout << str1 << ": " << hash1 << std::endl;

    std::cout << "abc1 : " << gdp::gdu::hash_code("abc1", 1<<31) << std::endl;
    return 0;
}
