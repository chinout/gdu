// copyright 2017 war10ck

#ifndef GDU_UTIL_HPP_
#define GDU_UTIL_HPP_

#include <string>
#include <vector>

namespace gdp {
namespace gdu {

typedef std::vector<std::string> Tokens;
inline void split(const std::string & src, const std::string & sep, std::vector<std::string> & tokens) {
    tokens.clear();
    std::string s;
    for(auto i = src.begin(); i != src.end(); i++) {
        if (sep.find(*i) != std::string::npos) {
            tokens.push_back(s);
            s = "";
        } else {
            s += *i;
        }
    }
    if ( s.length() || tokens.size() ) {
        tokens.push_back(s);
    }
}


}  // namespace gdu
}  // namespace gdp

#endif  // GDU_UTIL_HPP_
