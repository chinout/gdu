#include "unix.hpp"
#include <thread>
#include <fstream>
#include <iostream>

using namespace gdp::gdu;

static void OnSignal(int s);
void HookSignals();
void UnHookSignals();

class Master {
    public:
        static Master& instance() {
            static Master inst;
            return inst;
        }
        void start() {
            stop_ = false;
            HookSignals();
            out_ = std::ofstream("out.log");
            thread_ = std::thread(&Master::run, this);
            thread_.join();
        }
        void *run() {
            uint32_t cnt = 0; 
            while (!stop_) {
                cnt++;
                out_ << cnt << std::endl;
                std::cout << cnt << std::endl;
                sleep(1);
            }
            return this;
        }
        void stop() {
            stop_ = true;
            out_ << "stop" << std::endl;
            std::cout << "stop" << std::endl;
            UnHookSignals();
        }
    private:
        std::thread thread_;
        bool stop_;
        std::ofstream out_;
};

static void OnSignal(int s)
{
    switch (s)
    {
        case SIGINT:
        case SIGQUIT:
        case SIGTERM:
        case SIGABRT:
        case SIGUSR1:

            Master::instance().stop();

            break;
    }
    signal(s, OnSignal);
}

void HookSignals()
{
    signal(SIGINT, OnSignal);
    signal(SIGQUIT, OnSignal);
    signal(SIGTERM, OnSignal);
    signal(SIGABRT, OnSignal);
    signal(SIGPIPE, SIG_IGN);
    signal(SIGUSR1, OnSignal);
}

void UnHookSignals()
{
    signal(SIGINT, 0);
    signal(SIGQUIT, 0);
    signal(SIGTERM, 0);
    signal(SIGABRT, 0);
    signal(SIGUSR1, 0);
}

int main(int argc, char* argv[]) {
    if (argc == 2 && strcmp(argv[1], "-d") == 0) {
        std::cout << "daemon" << std::endl;

        CreateDaemon();
        SetRLimit();
        CreatePidFile();
    }

    std::cout << "no daemon" << std::endl;

    Master::instance().start();
    // Master::instance().stop();
    return 0;
}
