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

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class WebWriter {
private:
    static void do_session(std::string host,
                           std::string const &port,
                           std::string const &text,
                           net::io_context &ioc,
                           net::yield_context yield);
};


#endif //ORAN_INTERFACE_WEBWRITER_HPP
