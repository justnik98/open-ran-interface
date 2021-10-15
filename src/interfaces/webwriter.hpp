//
// Created by justnik on 16.10.2021.
//

#ifndef ORAN_INTERFACE_WEBWRITER_HPP
#define ORAN_INTERFACE_WEBWRITER_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/spawn.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include "iwriter.hpp"


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class WebWriter : public IWriter {
private:
    std::string host = "127.0.0.1";
    std::string port = "8080";
    static void doSession(std::string host, const std::string &port, const std::string &text, net::io_context &ioc,
                   const boost::asio::yield_context &yield);

    static void fail(beast::error_code ec, char const *what);

public:
    void write(const std::string &msg) override;
};


#endif //ORAN_INTERFACE_WEBWRITER_HPP
