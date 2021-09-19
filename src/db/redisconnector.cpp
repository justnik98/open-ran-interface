//
// Created by justnik on 17.09.2021.
//

#include <utility>
#include "redisconnector.hpp"

RedisConnector::RedisConnector(std::string ip, uint32_t port) : IP(std::move(ip)), port(port) {}

void RedisConnector::run() const {
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
    redisAsyncCommand(c, subCallback, (char *) "sub", "SUBSCRIBE foo");

    event_base_dispatch(base);
}


void subCallback(redisAsyncContext *c, void *r, void *priv) {
    auto *reply = static_cast<redisReply *> (r);
    if (reply == nullptr) return;
    if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3) {
        if (strcmp(reply->element[0]->str, "subscribe") != 0) {
            printf("Received[%s] channel %s: %s\n",
                   (char *) priv,
                   reply->element[1]->str,
                   reply->element[2]->str);
        }
    }
}

void connectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
        return;
    }
    printf("Connected...\n");
}

void disconnectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
        return;
    }
    printf("Disconnected...\n");
}
