#include "hash.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {
    uint64_t seed = 0xEE6B27EB;
    std::string str1 = "abc";
    uint32_t hash1 = gdp::gdu::MurmurHash64(str1.c_str(), str1.length(), seed);
    std::cout << str1 << ": " << hash1 << std::endl;

    std::cout << "abd : " << gdp::gdu::MurmurHash64("abd", 3, seed) << std::endl;

    return 0;
}
