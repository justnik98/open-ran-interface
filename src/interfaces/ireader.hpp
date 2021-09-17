//
// Created by justnik on 17.09.2021.
//

#ifndef ORAN_INTERFACE_IREADER_HPP
#define ORAN_INTERFACE_IREADER_HPP

#include <string>

class IReader {
public:
    virtual std::string read() = 0;
};


#endif //ORAN_INTERFACE_IREADER_HPP
