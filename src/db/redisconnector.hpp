//
// Created by justnik on 17.09.2021.
//

#ifndef ORAN_INTERFACE_REDISCONNECTOR_HPP
#define ORAN_INTERFACE_REDISCONNECTOR_HPP

#include <string>

class RedisConnector {
public:
    RedisConnector(std::string ip, uint32_t port);

    void run();

private:
    std::string IP = "127.0.0.1";
    uint32_t port = 6379;
};


#endif //ORAN_INTERFACE_REDISCONNECTOR_HPP
