#include "to_int.hpp"
#include <iostream>

using namespace gdp::gdu;
using namespace std;

int main() {
    cout << to_int("123") << endl;
    cout << to_int("1231afdal") << endl;
    return 0;
}
