//
// Created by justnik on 22.09.2021.
//

#ifndef ORAN_INTERFACE_CONCURRENTQUEUE_HPP
#define ORAN_INTERFACE_CONCURRENTQUEUE_HPP

#include <queue>
#include <mutex>

template<typename T>
class Concurrent_queue {
private:
    std::queue<T> q;
    mutable std::mutex mut;
public:
    void push(const T& data);
    bool empty();
    T& front();
    void pop();
};


#endif //ORAN_INTERFACE_CONCURRENTQUEUE_HPP
