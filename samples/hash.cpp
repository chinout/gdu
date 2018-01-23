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

    uint64_t input1 = 16791;
    uint64_t hash2 = gdp::gdu::MurmurHash64(&input1, 8, seed);
    std::cout << input1 << ": " << hash2 << std::endl;

    uint64_t input2 = 16792;
    std::cout << "16792 : " << gdp::gdu::MurmurHash64(&input2, 8, seed) << std::endl;
    return 0;
}
