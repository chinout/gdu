#include "consistent_locked_map.hpp"
#include "hash.hpp"
#include <iostream>

using namespace std;
using namespace gdp::gdu;

int main() {
    string nodes[] = {"127.0.0.1:1234", "127.0.0.1:1235", "127.0.0.1:1236"};
    ConsistentLockedMap<uint32_t, string> consistent_map;
    for (auto& node : nodes) {
        uint32_t hash = HashCode(node, 3);
        std::cout << hash << std::endl;
        consistent_map.insert(hash, node);
    }

    
    return 0;
}
