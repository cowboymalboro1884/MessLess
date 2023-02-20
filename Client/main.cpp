#include "client.h"

int main() {
    boost::asio::io_service io_service;
    // socket creation
    tcp::socket socket(io_service);
    // connection
    socket.connect(tcp::endpoint(
        boost::asio::ip::address::from_string("194.87.210.109"), 1234
    ));

    /* CONNECTION IS ESTABLISHED */

    // read from input stream

    char buf[4096];
    string msg;
    std::cout << ">";
    std::getline(std::cin, msg, '\n');
    std::strcpy(buf, msg.c_str());

    boost::system::error_code error;
    socket.send(boost::asio::buffer(buf));
    std::cout << "delivered: " << msg << std::endl;

    // request/message from client
    if (error) {
        std::cout << "send failed: " << error.message() << std::endl;
    }

    // getting response from server
    boost::asio::streambuf receive_buffer;
    boost::asio::read(
        socket, receive_buffer, boost::asio::transfer_all(), error
    );
    if (error && error != boost::asio::error::eof) {
        std::cout << "receive failed: " << error.message() << std::endl;
    } else {
        const char *data =
            boost::asio::buffer_cast<const char *>(receive_buffer.data());
        std::cout << "recieved: " << data << std::endl;
    }

    return 0;
}