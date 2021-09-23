//
// Created by justnik on 17.09.2021.
//

#include <iostream>
#include <string>
#include <thread>
#include "controller.hpp"

using namespace std;

void Controller::run() {
    RedisConnector r("127.0.0.1", 6379, tasks);
    //r.run();
    //r.setQueue(tasks);
    std::thread t1([&r]() { r.run(); });
    std::thread t2(&Controller::worker, this);
    std::thread t3(&Controller::worker, this);
    t1.detach();
    t2.join();
    t3.join();
}

[[noreturn]] void Controller::worker() {
    string res;
    while (true) {
        tasks.wait_and_pop(res);
        cout << res << endl;
    }
}
