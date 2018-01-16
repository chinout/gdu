#include "time.hpp"
#include <iostream>

using namespace std;
using namespace gdp::gdu;

int main() {
    cout << get_time() << endl;
    cout << get_millisecond() << endl;
    cout << get_date() << endl;

    auto cur_time = get_time();
    cur_time += kDay * 5 + kHour * 4 + kMinute * 30;
    cout << cur_time << endl;
    return 0;
}
