//
// Created by justnik on 17.09.2021.
//

#ifndef ORAN_INTERFACE_REDISCONNECTOR_HPP
#define ORAN_INTERFACE_REDISCONNECTOR_HPP

#include <string>
#include <cstring>
#include <csignal>
#include "hiredis/async.h"
#include "hiredis/hiredis.h"
#include "hiredis/adapters/libevent.h"
#include "../queue/concurrentqueue.hpp"

class RedisConnector {
private:
    std::string IP = "127.0.0.1";
    uint32_t port = 6379;

public:

    RedisConnector(std::string ip, uint32_t port, Concurrent_queue<std::string> &tasks);

    explicit RedisConnector(Concurrent_queue<std::string> &tasks);

    void run();

private:

    Concurrent_queue<std::string> &tasks;

    static void subCallback(redisAsyncContext *c, void *r, void *priv);

    static void connectCallback(const redisAsyncContext *c, int status);

    static void disconnectCallback(const redisAsyncContext *c, int status);
};


#endif //ORAN_INTERFACE_REDISCONNECTOR_HPP
