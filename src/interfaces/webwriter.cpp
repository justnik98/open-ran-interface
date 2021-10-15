//
// Created by justnik on 16.10.2021.
//

#include "webwriter.hpp"

void WebWriter::fail(beast::error_code ec, char const *what) {
    std::cerr << what << ": " << ec.message() << "\n";
}

void WebWriter::doSession(
        std::string host,
        std::string const &port,
        std::string const &text,
        net::io_context &ioc,
        const net::yield_context &yield) {
    beast::error_code ec;

    // These objects perform our I/O
    tcp::resolver resolver(ioc);
    websocket::stream<beast::tcp_stream> ws(ioc);

    // Look up the domain name
    auto const results = resolver.async_resolve(host, port, yield[ec]);
    if (ec)
        return fail(ec, "resolve");

    // Set a timeout on the operation
    beast::get_lowest_layer(ws).expires_after(std::chrono::seconds(30));

    // Make the connection on the IP address we get from a lookup
    auto ep = beast::get_lowest_layer(ws).async_connect(results, yield[ec]);
    if (ec)
        return fail(ec, "connect");

    // Update the host_ string. This will provide the value of the
    // Host HTTP header during the WebSocket handshake.
    // See https://tools.ietf.org/html/rfc7230#section-5.4
    host += ':' + std::to_string(ep.port());

    // Turn off the timeout on the tcp_stream, because
    // the websocket stream has its own timeout system.
    beast::get_lowest_layer(ws).expires_never();

    // Set suggested timeout settings for the websocket
    ws.set_option(
            websocket::stream_base::timeout::suggested(
                    beast::role_type::client));

    // Set a decorator to change the User-Agent of the handshake
    ws.set_option(websocket::stream_base::decorator(
            [](websocket::request_type &req) {
                req.set(http::field::user_agent,
                        std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-client-coro");
            }));

    // Perform the websocket handshake
    ws.async_handshake(host, "/", yield[ec]);
    if (ec)
        return fail(ec, "handshake");

    // Send the message
    ws.async_write(net::buffer(std::string(text)), yield[ec]);
    if (ec)
        return fail(ec, "write");

    // This buffer will hold the incoming message
    beast::flat_buffer buffer;

    // Read a message into our buffer
    ws.async_read(buffer, yield[ec]);
    if (ec)
        return fail(ec, "read");

    // Close the WebSocket connection
    ws.async_close(websocket::close_code::normal, yield[ec]);
    if (ec)
        return fail(ec, "close");

    // If we get here then the connection is closed gracefully

    // The make_printable() function helps print a ConstBufferSequence
    std::cout << beast::make_printable(buffer.data()) << std::endl;
}
