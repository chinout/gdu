#include "unix.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace gdp::gdu;

class Master {
 public:
    static void run() {
        ofstream out("out.log");
        while (true) {
            out << "111" << endl;
            sleep(1);
        }
    } 
};

int main() {
    CreateDaemon();

    SetRLimit();

    CreatePidFile();

    Master::run(); 
    return 0;
}
