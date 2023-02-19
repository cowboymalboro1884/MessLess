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
    // read operation
    string message = server.read_(socket_);
    std::cout << message << std::endl;
    // write operation
    server.send_(socket_, message);
}