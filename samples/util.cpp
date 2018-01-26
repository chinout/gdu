#include "util.hpp"
#include <iostream>

using namespace gdp::gdu;
using namespace std;

int main() {
    std::string broker = "127.0.0.1:1024";
    Tokens tokens;
    split(broker, ":", tokens);
    for (auto token : tokens) {
        cout << token << endl;
    }

    return 0; 
}
