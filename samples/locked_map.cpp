#include "locked_map.hpp"
#include <iostream>

using namespace std;
using namespace gdp::gdu;

int main() {
    LockedMap<int, int> lmap;
    lmap.insert(1, 1);
    lmap.insert(2, 2);
    int second;
    bool ret = lmap.find(2, second);
    cout << lmap.size() << endl;
    cout << second << endl;
    
    lmap.erase(2);
    cout << lmap.size() << endl;
    return 0;
}
