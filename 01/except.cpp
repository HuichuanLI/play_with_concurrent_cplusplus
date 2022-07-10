//
// Created by lhc456 on 2022/7/10.
//
#include <thread>

int main() {
    std::thread t([] {});
    try {
        throw 0;
    } catch (int x) {
        t.join();  // 处理异常前先 join()
        throw x;   // 再将异常抛出
    }
    t.join();  // 之前抛异常，不会执行到此处
}