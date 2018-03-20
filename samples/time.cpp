#include "time.hpp"
#include <iostream>

using namespace std;
using namespace gdp::gdu;

class Master {
 public:
    void start() {
        manager_.AddTask(this, 1 * kInMilliSecond, &Master::Update1Sec);
        manager_.AddTask(this, 3 * kInMilliSecond, &Master::Update3Sec);
        manager_.AddTask(this, 3 * kMinute * kInMilliSecond, &Master::Update3Min);

        while (true) {
            manager_.Tick();    
        }
    }

    void Update1Sec() {
        cout << "Update1Sec: " << get_time() << endl;
    }

    void Update3Sec() {
        cout << "Update3Sec: " << get_time() << endl;
    }

    void Update3Min() {
        cout << "Update3Min: " << get_time() << endl;
    }

 private:
    TimerManager manager_;
    //Is this still needed?? [On linux some time ago not working 50ms]
    const uint32_t kSleepConst = 100;
};

int main() {
    cout << kDay << endl;
    cout << kMonth << endl;
    cout << kYear << endl;
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
