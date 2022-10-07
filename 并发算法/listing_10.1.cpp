
#include <iostream>
#include <exception>
#include <stack>
#include <mutex>
#include <memory>

using namespace std;


class X {
    mutable std::mutex m;
    int data;
public:
    X() : data(0) {}

    int get_value() const {
        std::lock_guard guard(m);
        return data;
    }

    void increment() {
        std::lock_guard guard(m);
        ++data;
    }
};

void increment_all(std::vector<X> &v) {
    std::for_each(std::execution::parallel_policy, v.begin(), v.end(),
                  [](X &x) {
                      x.increment();
                  });
}
