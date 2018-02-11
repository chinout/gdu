// copyright 2017 war10ck

#ifndef GDU_TO_INT_HPP_
#define GDU_TO_INT_HPP_

#include <sstream>
#include <string>

namespace gdp {
namespace gdu {

inline int to_int(const std::string& input) {
    int ret = 0;
    std::stringstream ostr;
    ostr << input;
    ostr >> ret;
    return ret;
}

inline uint32_t to_uint32(const std::string& input) {
    uint32_t ret = 0;
    std::stringstream ostr;
    ostr << input;
    ostr >> ret;
    return ret;
}

}  // namespace gdu
}  // namespace gdp

#endif  // GDU_TO_INT_HPP_
