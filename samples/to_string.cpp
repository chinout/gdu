#include "to_string.hpp"
#include <utility>
#include <map>
#include <set>
#include <vector>
#include <iostream>

using namespace std;
using namespace gdp::gdu;

int main() {
    cout << to_string(123123) << endl;
    auto pair = make_pair(1, 2);
    cout << to_string(pair) << endl;
    vector<int> vec{1, 2, 3};
    cout << to_string(vec) << endl;
    map<int, const char*> map{{101, "c++"}, {102, "java"}};
    cout << to_string(map) << endl;
    return 0;
}
