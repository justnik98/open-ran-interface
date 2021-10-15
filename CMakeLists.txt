cmake_minimum_required(VERSION 3.16)
project(oran-interface)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(oran-interface main.cpp src/controller/controller.cpp src/db/redisconnector.cpp src/queue/concurrentqueue.hpp src/interfaces/consolewriter.cpp src/interfaces/consolewriter.hpp src/interfaces/webwriter.cpp src/interfaces/webwriter.hpp)
target_link_libraries(oran-interface PUBLIC ${CONAN_LIBS})
