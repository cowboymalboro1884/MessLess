#include "server.h"

int main() {
    server::Server server;
    boost::asio::io_service io_service;
    // listen for new connection
    tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234));
    // socket creation
    tcp::socket socket_(io_service);
    // waiting for connection
    acceptor_.accept(socket_);

    /* CONNECTION IS ESTABLISHED */

    // read operation
    std::cout << "waiting for message" << std::endl;
    string message = server.read_(socket_);
    std::cout << message << std::endl;

    // send
    server.send_(socket_, message);
    std::cout << "succesfully send" << std::endl;
    socket_.close();
}