#include "singleton.hpp"
#include <iostream>


class Foo {
public:
    int foo() {
        return foo_;
    }
    void set_foo(int x) {
        foo_ = x;
    }
private:
    int foo_;
};

#define sFoo gdp::gdu::Singleton<Foo>::get_instance()

int main() {
    sFoo.set_foo(1); 
    std::cout << sFoo.foo() << std::endl;
    return 0;
}

