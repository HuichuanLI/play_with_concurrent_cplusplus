//
// Created by lhc456 on 2022/7/10.
//
#include <cassert>
#include <thread>
#include <iostream>

class A {
public:
    void f(int i) { std::cout << i; }
};


void f(int &i) { ++i; }

int main() {
    int i = 1;
    std::thread t{f, std::ref(i)};
    t.join();
    assert(i == 2);
    A a;
    std::thread t1{&A::f, &a, 42};  // 调用 a->f(42)
    std::thread t2{&A::f, a, 42};   // 拷贝构造 tmp_a，再调用 tmp_a.f(42)
    t1.join();
    t2.join();
}