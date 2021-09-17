//
// Created by justnik on 17.09.2021.
//

#include "redisconnector.hpp"

#include <utility>

RedisConnector::RedisConnector(std::string ip, uint32_t port) : IP(std::move(ip)), port(port) {}
