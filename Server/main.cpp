#include "server.h"

const int PORT = 1234;

int main() {
    server::Server server;
    boost::asio::io_service io_service;
    std::cout << "Server is started, waiting for connection...\n";
    // listen for new connection
    tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), PORT));
    // socket creation
    tcp::socket socket_(io_service);
    // waiting for connection
    acceptor_.accept(socket_);

    /* CONNECTION IS ESTABLISHED */
    std::cout << "Connection is established! Listening on port..." << PORT
              << std::endl;
    // read operation
    while (true) {
        try {
            std::string message = server.read_(socket_);
            std::cout << "succesfully red : " << message << "\n";
            if (message == "stop\n") {
                std::cout << "got \"stop\" command ==> closing the socket..."
                          << std::endl;
                socket_.close();
                break;
            }

            boost::asio::streambuf bf;
            server.send_(socket_, message);
            std::cout << "succesfully send" << std::endl;
        } catch (boost::system::system_error &e) {
            std::cout << "smth wrong>> " << std::endl;
            std::cout << e.what() << std::endl;
            socket_.close();
            throw;
        }
    }
}