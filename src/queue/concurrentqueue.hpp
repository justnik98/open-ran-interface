//
// Created by justnik on 22.09.2021.
//

#ifndef ORAN_INTERFACE_CONCURRENTQUEUE_HPP
#define ORAN_INTERFACE_CONCURRENTQUEUE_HPP

#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include <queue>


template<typename T>
class Concurrent_queue {
private:
    std::queue<T> q;
    boost::mutex mut;
    boost::condition_variable cond_var;

public:
    void push(const T &data);

    bool empty();

    void wait_and_pop(T &value);
};

template<typename T>
void Concurrent_queue<T>::push(const T &data) {
    boost::mutex::scoped_lock lock(mut);
    q.push(data);
    lock.unlock();
    cond_var.notify_one();
}

template<typename T>
bool Concurrent_queue<T>::empty() {
    boost::mutex::scoped_lock lock(mut);
    return q.empty();
}

template<typename T>
void Concurrent_queue<T>::wait_and_pop(T &value) {
    boost::mutex::scoped_lock lock(mut);
    while (q.empty()) {
        cond_var.wait(lock);
    }
    value = q.front();
    q.pop();
}


#endif //ORAN_INTERFACE_CONCURRENTQUEUE_HPP
