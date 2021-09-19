//
// Created by justnik on 17.09.2021.
//

#include "controller.hpp"

void Controller::run( const RedisConnector &c) {
    c.run();
}
