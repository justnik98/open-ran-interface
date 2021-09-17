cmake_minimum_required(VERSION 3.20)
project(oran_interface)

set(CMAKE_CXX_STANDARD 20)

add_executable(oran_interface main.cpp src/controller/controller.cpp src/controller/controller.hpp src/interfaces/iwriter.hpp src/interfaces/ireader.hpp src/db/redisconnector.cpp src/db/redisconnector.hpp)
