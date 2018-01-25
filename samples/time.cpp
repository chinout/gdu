#include "time.hpp"
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace gdp::gdu;

class Master {
 public:
    void start() {
        uint32_t current_time = 0;
        uint32_t previous_time = get_millisecond();
        uint32_t previous_sleep_time = 0;
        manager_.AddTask(this, 1 * kInMilliSecond, &Master::Update1Sec);
        // manager_.AddTask(this, 3 * kInMilliSecond, &Master::Update3Sec);
        // manager_.AddTask(this, 3 * kMinute * kInMilliSecond, &Master::Update3Min);

        while (true) {
            current_time = get_millisecond();

            time_t diff;
            // get_millisecond() have limited data range and this is case when it overflow in this tick
            if (previous_time > current_time)
                diff = 0xFFFFFFFFFFFFFFFF - (previous_time - current_time);
            else
                diff = current_time - previous_time;
            
            manager_.Update(diff);
            previous_time = current_time;

            // diff (D0) include time of previous sleep (d0) + tick time (t0)
            // we want that next d1 + t1 == kSleepConst
            // we can't know next t1 and then can use(t0 + d1) == kSleepConst requirement
            // d1 = kSleepConst - t0 = kSleepConst - (D0 - d0) = kSleepConst + d0 - D0
            if (diff <= kSleepConst + previous_sleep_time) {
                usleep(kSleepConst * 1000);
            } else {
                previous_sleep_time = 0;
            }
        }
    }

    void Update1Sec() {
        cout << get_time() << endl;
    }

    void Update3Sec() {
        cout << get_time() << endl;
    }

    void Update3Min() {
        cout << get_time() << endl;
    }
 private:
    TimerManager manager_;
    //Is this still needed?? [On linux some time ago not working 50ms]
    const uint32_t kSleepConst = 100;
};

int main() {
    cout << get_time() << endl;
    cout << get_millisecond() << endl;
    cout << get_date() << endl;

    auto cur_time = get_time();
    cur_time += kDay * 5 + kHour * 4 + kMinute * 30;
    cout << cur_time << endl;

    Master master;
    master.start();
    return 0;
}
