//
// Created by justnik on 17.09.2021.
//

#ifndef ORAN_INTERFACE_IWRITER_HPP
#define ORAN_INTERFACE_IWRITER_HPP

#include <string>

class IWriter {
public:
    virtual void write(const std::string &msg) = 0;
};


#endif //ORAN_INTERFACE_IWRITER_HPP
