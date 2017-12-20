// copyright 2017 war10ck

#ifndef GDU_TO_STRING_HPP_
#define GDU_TO_STRING_HPP_

#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>

namespace gdp {
namespace gdu {

template <typename T>
std::string to_string(const T& t) {
    return std::to_string(t);
}

template <typename K, typename V>
std::string to_string(const std::map<K, V>& m);

template <typename T>
std::string to_string(const std::set<T>& s);

template <typename T>
std::string to_string(const std::vector<T>& t);

template <typename K, typename V>
std::string to_string(const typename std::pair<K, V>& v) {
    std::ostringstream o;
    o << to_string(v.first) << ": " << to_string(v.second);
    return o.str();
}

template <typename T>
std::string to_string(const T& beg, const T& end)
{
    std::ostringstream o;
    for (T it = beg; it != end; ++it) {
        if (it != beg) {
            o << ", ";
        }
        o << to_string(*it);
    }
    return o.str();
}

template <typename T>
std::string to_string(const std::vector<T>& t) {
    std::ostringstream o;
    o << "[" << to_string(t.begin(), t.end()) << "]";
    return o.str();
}

template <typename K, typename V>
std::string to_string(const std::map<K, V>& m) {
    std::ostringstream o;
    o << "{" << to_string(m.begin(), m.end()) << "}";
    return o.str();
}

template <typename T>
std::string to_string(const std::set<T>& s) {
    std::ostringstream o;
    o << "{" << to_string(s.begin(), s.end()) << "}";
    return o.str();
}

} // namespace gdu
} // namespace gdp

#endif  // GDU_TO_STRING_HPP_
