//
// Created by lhc456 on 2022/7/10.
//
#include <thread>
#include <utility>

void f() {}

void g() {}

int main() {
    std::thread a{f};
    std::thread b = std::move(a);
    assert(!a.joinable());
    assert(b.joinable());
    a = std::thread{g};
    assert(a.joinable());
    assert(b.joinable());
    // a = std::move(b);  // 错误，不能转移所有权到 joinable 的线程
    a.join();
    a = std::move(b);
    assert(a.joinable());
    assert(!b.joinable());
    a.join();
}