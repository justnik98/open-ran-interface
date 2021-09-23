//
// Created by justnik on 17.09.2021.
//

#include <utility>
#include "redisconnector.hpp"

RedisConnector::RedisConnector(std::string ip, uint32_t port, Concurrent_queue<std::string> &tasks)
        : IP(std::move(ip)), port(port), tasks(tasks) {}

RedisConnector::RedisConnector(Concurrent_queue<std::string> &tasks) : tasks(tasks) {}

void RedisConnector::run() {
    signal(SIGPIPE, SIG_IGN);
    struct event_base *base = event_base_new();

    redisAsyncContext *c = redisAsyncConnect(IP.c_str(), port);
    if (c->err) {
        /* Let *c leak for now... */
        printf("Error: %s\n", c->errstr);
        throw 42;
    }

    redisLibeventAttach(c, base);
    redisAsyncSetConnectCallback(c, connectCallback);
    redisAsyncSetDisconnectCallback(c, disconnectCallback);
    redisAsyncCommand(c, subCallback, &tasks, "SUBSCRIBE foo");

    event_base_dispatch(base);
}

void RedisConnector::subCallback(redisAsyncContext *c, void *r, void *priv) {
    auto *reply = static_cast<redisReply *> (r);
    if (reply == nullptr) return;
    auto t = static_cast<Concurrent_queue<std::string> *> (priv);
    if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3) {
        if (strcmp(reply->element[0]->str, "subscribe") != 0) {
            t->push(reply->element[2]->str);
        }
    }
}

void RedisConnector::connectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
        return;
    }
    printf("Connected...\n");
}

void RedisConnector::disconnectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
        return;
    }
    printf("Disconnected...\n");
}


