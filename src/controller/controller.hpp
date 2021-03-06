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
    Controller();

    void run();

private:
    Concurrent_queue<std::string> tasks;

    uint32_t thread_count = 2;

    std::map<std::string, std::string> params;

    void readConfig();

    static void replace_all(std::string& inout, std::string_view what, std::string_view with);

    [[noreturn]] void worker();
};


#endif //ORAN_INTERFACE_CONTROLLER_HPP
