//
// Created by lhc456 on 2022/7/10.
//
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

class A {
public:
    void wait1() {
        std::unique_lock<std::mutex> l(m_);
        cv_.wait(l, [this] { return done_; });
        std::cout << 1;
    }

    void wait2() {
        std::unique_lock<std::mutex> l(m_);
        cv_.wait(l, [this] { return done_; });
        std::cout << 2;
    }

    void signal() {
        {
            std::lock_guard<std::mutex> l(m_);
            done_ = true;
        }
        cv_.notify_all();
    }

private:
    std::mutex m_;
    std::condition_variable cv_;
    bool done_ = false;
};

int main() {
    A a;
    std::thread t1(&A::wait1, &a);
    std::thread t2(&A::wait2, &a);
    std::thread t3(&A::signal, &a);
    t1.join();
    t2.join();
    t3.join();
}  // 12 or 21