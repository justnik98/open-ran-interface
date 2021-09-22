#include <iostream>
#include "src/controller/controller.hpp"
#include "src/interfaces/iwriter.hpp"
#include "src/interfaces/ireader.hpp"

int main() {

    Controller c;
    RedisConnector r;
    Controller::run(r);
    return 0;
}
