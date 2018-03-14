#include "locked_queue.hpp"
#include <iostream>

using namespace std;
using namespace gdp::gdu;

int main() {
    LockedQueue<int> lqueue;
    lqueue.add(1);
    lqueue.add(2);
    lqueue.add(3);

    int res;
    while (lqueue.next(res)) {
        cout << lqueue.size() << " ";
        cout << res << endl;
    }
    
    return 0;
}
