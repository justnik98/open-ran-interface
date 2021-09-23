//
// Created by justnik on 17.09.2021.
//

#ifndef ORAN_INTERFACE_CONTROLLER_HPP
#define ORAN_INTERFACE_CONTROLLER_HPP

#include <string>
#include "../db/redisconnector.hpp"
#include "../interfaces/ireader.hpp"
#include "../interfaces/iwriter.hpp"
#include "../queue/concurrentqueue.hpp"


class Controller {
public:
    Controller() = default;

    void run();

private:
    Concurrent_queue<std::string> tasks;

    [[noreturn]] void worker();
};


#endif //ORAN_INTERFACE_CONTROLLER_HPP
