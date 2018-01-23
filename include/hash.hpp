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

// MurmurHash2, by Austin Appleby
// Note - This code makes a few assumptions about how your machine behaves -
// And it has a few limitations -
// 1. It will not work incrementally.
// 2. It will not produce the same results on little-endian and big-endian
//    machines.

inline uint64_t MurmurHash64 ( const void * key, int len, unsigned int seed ) {
    const uint64_t m = 0xc6a4a7935bd1e995;
    const int r = 47;

    uint64_t h = seed ^ (len * m);

    const uint64_t * data = (const uint64_t *)key;
    const uint64_t * end = data + (len/8);

    while(data != end) {
        uint64_t k = *data++;

        k *= m; 
        k ^= k >> r; 
        k *= m; 

        h ^= k;
        h *= m; 
    }

    const unsigned char * data2 = (const unsigned char*)data;

    switch(len & 7)
    {
        case 7: h ^= uint64_t(data2[6]) << 48;
        case 6: h ^= uint64_t(data2[5]) << 40;
        case 5: h ^= uint64_t(data2[4]) << 32;
        case 4: h ^= uint64_t(data2[3]) << 24;
        case 3: h ^= uint64_t(data2[2]) << 16;
        case 2: h ^= uint64_t(data2[1]) << 8;
        case 1: h ^= uint64_t(data2[0]);
                h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
} 


}  // namespace gdu
}  // namespace gdp

#endif  // GDU_TO_INT_HPP_
