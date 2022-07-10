//
// Created by lhc456 on 2022/7/10.
//
#include <list>
#include <mutex>
#include <algorithm>

std::list<int> some_list;    // 1
std::mutex some_mutex;    // 2

void add_to_list(int new_value) {
    std::lock_guard<std::mutex> guard(some_mutex);    // 3
    some_list.push_back(new_value);
}

bool list_contains(int value_to_find) {
    std::lock_guard<std::mutex> guard(some_mutex);    // 4
    return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}

#include <iostream>

int main() {
    add_to_list(42);
    std::cout << "contains(1)=" << list_contains(1) << ", contains(42)=" << list_contains(42) << std::endl;
}
