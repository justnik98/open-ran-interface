//
// Created by justnik on 26.09.2021.
//

#ifndef ORAN_INTERFACE_CONSOLEWRITER_HPP
#define ORAN_INTERFACE_CONSOLEWRITER_HPP

#include "iwriter.hpp"

class ConsoleWriter : public IWriter {
public:
    void write(const std::string &msg) final;
};


#endif //ORAN_INTERFACE_CONSOLEWRITER_HPP
