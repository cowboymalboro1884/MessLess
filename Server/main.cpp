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
    std::cout << "Connection is established!" << std::endl;

    // read operation
    while (true) {
        try {
            std::string message = server.read_(socket_);
            std::cout << "succesfully red >> ";
            std::cout << message << std::endl;
            if (message == "stop") {
                std::cout << "got \"stop\" command ==> closing the socket...\n";
                socket_.close();
                break;
            }

            boost::asio::streambuf bf;
            server.send_(socket_, message);
            std::cout << "succesfully send" << std::endl;
        } catch (boost::system::system_error &e) {
            std::cout << "smth wrong>> " << std::endl;
            std::cout << e.code() << std::endl;
            socket_.close();
            throw;
        }
    }
    socket_.close();
}