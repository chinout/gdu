// copyright 2017 war10ck

#ifndef GDU_HASH_HPP_
#define GDU_HASH_HPP_

#include <string>

namespace gdp {
namespace gdu {

// return a hash code for the input, as Java hashCode() 
// use horner's rule : s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
inline uint32_t hash_code(const std::string& input, uint32_t mod) {
    uint32_t result = 0;
    uint32_t radis = 31;
    for (auto i = 0; i < input.length(); i++) {
        result = (radis * result + input[i]) % mod;
    }
    return result;
}

inline uint32_t hash_code(const uint32_t input, uint32_t mod) {
    return input % mod;
}

}  // namespace gdu
}  // namespace gdp

#endif  // GDU_TO_INT_HPP_
