//
// Created by justnik on 17.09.2021.
//

#ifndef ORAN_INTERFACE_CONTROLLER_HPP
#define ORAN_INTERFACE_CONTROLLER_HPP

#include "../db/redisconnector.hpp"
#include "../interfaces/ireader.hpp"
#include "../interfaces/iwriter.hpp"


class Controller {
public:
    Controller() = default;

    static void run(const RedisConnector &c);
};


#endif //ORAN_INTERFACE_CONTROLLER_HPP
