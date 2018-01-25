// copyright 2017 war10ck

#ifndef GDU_TIME_HPP_
#define GDU_TIME_HPP_

#include <ctime>
#include <chrono>
#include <string>
#include <functional>
#include <list>
#include <memory>

namespace gdp {
namespace gdu {

enum TimeConstants
{
    kMinute         = 60,
    kHour           = kMinute * 60,
    kDay            = kHour * 24,
    kWeek           = kDay * 7,
    kMonth          = kDay * 30,
    kYear           = kMonth * 12,
    kInMilliSecond  = 1000,
};

inline uint32_t get_time() {
    std::time_t time = std::time(nullptr);
    return time;
}

inline uint64_t get_millisecond() {
    return std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::system_clock::now().time_since_epoch()).count();
}

inline std::string get_date() {
    auto tt = std::chrono::system_clock::to_time_t  
            (std::chrono::system_clock::now());
    struct tm* ptm = localtime(&tt);
    char date[10] = {0};
    sprintf(date, "%d%02d%02d",
            (int)ptm->tm_year + 1900,(int)ptm->tm_mon + 1,(int)ptm->tm_mday);
    return std::string(date);  
}

class IntervalTimer
{
 public:
    IntervalTimer(): interval_(0), current_(0) {
    }

    void Update(time_t diff) {
        current_ += diff;
        if (current_ < 0) {
            current_ = 0;
        }
    }

    bool Passed() {
        return current_ >= interval_;
    }

    void Reset() {
        if (current_ >= interval_)
            current_ -= interval_;
    }

    void set_current(time_t current) {
        current_ = current;
    }

    void set_interval(time_t interval) {
        interval_ = interval;
    }

    time_t get_interval() const {
        return interval_;
    }

    time_t get_current() const {
        return current_;
    }

 private:
    time_t interval_;
    time_t current_;
};

class TimerTask {
 public:
    TimerTask() = default;
    virtual ~TimerTask() = default;
    
    explicit TimerTask(uint32_t interval, std::function<void()> f) {
        timer_.set_interval(interval);
        func_ = f;
    }

    void Update(uint32_t diff) {
        timer_.Update(diff);
        if (timer_.Passed()) {
            timer_.Reset();
            func_();
        }
    } 

 private:
    IntervalTimer timer_;
    std::function<void()> func_;
};

class TimerManager {
 public:
    TimerManager() = default;
    virtual ~TimerManager() = default;

    template<typename Obj>
    void AddTask(Obj* obj, uint32_t interval, void (Obj::*func)()) {
        tasks_.push_back(
                std::make_shared<TimerTask>(interval,
                   std::bind(func, obj)));
    }

    void Update(uint32_t diff) {
        for (auto task : tasks_) {
            if (task) {
                task->Update(diff);
            }
        }
    }

 private:
    std::list<std::shared_ptr<TimerTask> > tasks_;
};

}  // namespace gdu
}  // namespace gdp

#endif  // GDU_TIME_HPP_
