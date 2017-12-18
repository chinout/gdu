// copyright 2017 war10ck

#ifndef GDU_TIME_HPP_
#define GDU_TIME_HPP_

#include <ctime>
#include <chrono>

namespace gdp {
namespace gdu {

uint32_t get_time() {
    std::time_t time = std::time(nullptr);
    return time;
}

uint64_t get_millisecond() {
    return std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::system_clock::now().time_since_epoch()).count();
}

}  // namespace gdu
}  // namespace gdp

#endif  // GDU_TIME_HPP_