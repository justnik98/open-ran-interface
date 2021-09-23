//
// Created by justnik on 17.09.2021.
//

#include <iostream>
#include <string>
#include <thread>
#include "controller.hpp"

using namespace std;

Controller::Controller(uint32_t threadCount) : thread_count(threadCount) {}

void Controller::run() {
    RedisConnector r(tasks);
    vector<thread> threads;
    threads.emplace_back(thread([&r]() { r.run(); }));
    for (auto i = 1; i < thread_count; ++i)
        threads.emplace_back(thread(&Controller::worker, this));

    threads[0].detach();
    for (auto &&t: threads) {
        if (t.joinable()) {
            t.join();
        }
    }

}

[[noreturn]] void Controller::worker() {
    string res;
    while (true) {
        tasks.wait_and_pop(res);
        cout << res << endl;
    }
}


