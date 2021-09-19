//
// Created by justnik on 17.09.2021.
//

#ifndef ORAN_INTERFACE_REDISCONNECTOR_HPP
#define ORAN_INTERFACE_REDISCONNECTOR_HPP

#include <string>
#include <cstring>
#include <csignal>
#include "hiredis/hiredis.h"
#include "hiredis/async.h"
#include "hiredis/adapters/libevent.h"

class RedisConnector {
public:
    RedisConnector() = default;

    RedisConnector(std::string ip, uint32_t port);

    void run() const;

private:
    std::string IP = "127.0.0.1";
    uint32_t port = 6379;
};

void subCallback(redisAsyncContext *c, void *r, void *priv);

void connectCallback(const redisAsyncContext *c, int status);

void disconnectCallback(const redisAsyncContext *c, int status);

#endif //ORAN_INTERFACE_REDISCONNECTOR_HPP
