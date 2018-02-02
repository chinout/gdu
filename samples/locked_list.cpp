#include "locked_list.hpp"
#include <iostream>

using namespace std;
using namespace gdp::gdu;

int main() {
    LockedList<int> lst;
    lst.push_back(2);
    auto ret = lst.front();
    cout << lst.size() << endl;
    cout << ret << endl;
    
    lst.pop_front();
    cout << lst.size() << endl;
    return 0;
}
