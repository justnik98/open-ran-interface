//
// Created by justnik on 17.09.2021.
//

#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <thread>
#include "controller.hpp"
#include "../interfaces/consolewriter.hpp"

using namespace std;

Controller::Controller() {
    readConfig();
    thread_count = stoi(params["MAX_NUMBER_OF_THREADS"]);
}

void Controller::run() {
    replace_all(params["TOPICS"], ",", " ");
    RedisConnector r(params["REDIS_IP"], stoi(params["REDIS_PORT"]), tasks, params["TOPICS"]);
    vector<thread> threads;
    threads.emplace_back(thread([&r]() { r.run(); }));
    for (auto i = 1; i < thread_count; ++i)
        threads.emplace_back(thread(&Controller::worker, this));

    threads[0].detach();
    for (auto &&t: threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}

[[noreturn]] void Controller::worker() {
    string res;
    ConsoleWriter w;
    while (true) {
        tasks.wait_and_pop(res);
        w.write(res);
    }
}

void Controller::readConfig() {
    ifstream in("../config.cf");
    if (!in.is_open()) {
        throw invalid_argument("There is no file named config.cf!");
    }
    std::string line;
    while (!in.eof()) {
        getline(in, line);
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (line.starts_with('#')) continue;
        auto pos = line.find('=');
        if (pos == string::npos) continue;
        string param = line.substr(0, pos);
        string value = line.substr(pos + 1, line.size());
        cout << param << ":::" << value << endl;
        params.insert(make_pair(param, value));
    }

    //Default params

    params.try_emplace("REDIS_IP", "127.0.0.1");
    params.try_emplace("REDIS_PORT", "6379");
    params.try_emplace("MAX_THREAD_COUNT", "2");
}

void Controller::replace_all(string &inout, std::string_view what, std::string_view with) {
    std::size_t count{};
    for (std::string::size_type pos{};
         std::string::npos != (pos = inout.find(what.data(), pos, what.length()));
         pos += with.length(), ++count) {
        inout.replace(pos, what.length(), with.data(), with.length());
    }
}


