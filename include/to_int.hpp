// copyright 2017 war10ck

#ifndef GDU_TO_INT_HPP_
#define GDU_TO_INT_HPP_

#include <sstream>
#include <string>

namespace gdp {
namespace gdu {

template<typename T>
inline T to_int(const std::string& input) {
    T ret = 0;
    std::stringstream ostr;
    ostr << input;
    ostr >> ret;
    return ret;
}

}  // namespace gdu
}  // namespace gdp

#endif  // GDU_TO_INT_HPP_
