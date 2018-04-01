// copyright 2017 war10ck

#ifndef GDU_TIME_HPP_
#define GDU_TIME_HPP_

#include <ctime>
#include <chrono>
#include <string>
#include <functional>
#include <list>
#include <memory>
#include <unistd.h>

namespace gdp {
namespace gdu {

const uint64_t kSecond         = 1000;
const uint64_t kMinute         = kSecond * 60;
const uint64_t kHour           = kMinute * 60;
const uint64_t kDay            = kHour * 24;
const uint64_t kWeek           = kDay * 7;
const uint64_t kMonth          = kDay * 30;
const uint64_t kYear           = kMonth * 12;

inline uint64_t get_time() {
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
    
    explicit TimerTask(uint64_t interval, std::function<void()> f) {
        timer_.set_interval(interval);
        func_ = f;
    }

    void Update(uint64_t diff) {
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
    TimerManager():current_time_(0), previous_sleep_time_(0) {
        previous_time_ = get_millisecond();
    }
    virtual ~TimerManager() = default;

    template<typename Obj>
    void AddTask(Obj* obj, uint64_t interval, void (Obj::*func)()) {
        tasks_.push_back(
                std::make_shared<TimerTask>(interval,
                   std::bind(func, obj)));
    }

    void Tick() {
        current_time_ = get_millisecond(); 

        time_t diff;
        // get_millisecond() have limited data range and this is case when it
        // overflow in this tick
        if (previous_time_ > current_time_) {
            diff = 0xFFFFFFFFFFFFFFFF - (previous_time_ - current_time_);
        } else {
            diff = current_time_ - previous_time_;
        }
        Update(diff);
        
        previous_time_ = current_time_;

        // diff (D0) include time of previous sleep (d0) + tick time (t0)
        // we want that next d1 + t1 == kSleepConst
        // we can't know next t1 and then can use(t0 + d1) == kSleepConst requirement
        // d1 = kSleepConst - t0 = kSleepConst - (D0 - d0) = kSleepConst + d0 - D0
        if (diff <= kSleepConst + previous_sleep_time_) {
            previous_sleep_time_ = kSleepConst + previous_sleep_time_ - diff;
            usleep(kSleepConst * 1000);
        } else {
            previous_sleep_time_ = 0;
        }
    }

 private:

    void Update(uint64_t diff) {
        for (auto task : tasks_) {
            if (task) {
                task->Update(diff);
            }
        }
    }

 private:
    //Is this still needed?? [On linux some time ago not working 50ms]
    const uint64_t kSleepConst = 100;

    uint64_t current_time_;
    uint64_t previous_time_;
    uint64_t previous_sleep_time_;

    std::list<std::shared_ptr<TimerTask> > tasks_;
};

}  // namespace gdu
}  // namespace gdp

#endif  // GDU_TIME_HPP_
