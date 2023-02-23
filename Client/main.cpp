#include "client.h"

const int PORT = 1234;
const std::string IP_ADDRESS = "194.87.210.109";

int main() {
    boost::asio::io_service io_service;
    // socket creation
    tcp::socket socket(io_service);
    // connection
    socket.connect(
        tcp::endpoint(boost::asio::ip::address::from_string(IP_ADDRESS), PORT)
    );

    /* CONNECTION IS ESTABLISHED */
    std::cout << "You just connected to server with IP " << IP_ADDRESS
              << " and port " << PORT << "\n";
    std::cout << "To disconnect from server type \"stop\".\n" << std::endl;

    // read from input stream
    string msg;
    std::cout << ">";
    while (std::getline(std::cin, msg, '\n')) {
        boost::system::error_code error;
        const string message = msg + "\n";
        boost::asio::write(socket, boost::asio::buffer(message), error);
        if (msg == "stop") {
            std::cout << "Got \"stop\" command ==> closing the socket...\n";
            socket.close();
            return 0;
        }
        // request/message from client
        if (error) {
            std::cout << "send failed: " << error.message() << std::endl;
        }

        // getting response from server
        boost::asio::streambuf receive_buffer;
        boost::asio::read_until(socket, receive_buffer, "\n", error);
        if (error && error != boost::asio::error::eof) {
            std::cout << "receive failed: " << error.message() << std::endl;
        } else {
            const char *data =
                boost::asio::buffer_cast<const char *>(receive_buffer.data());
            std::cout << "recieved: " << data << std::endl;
        }
        std::cout << ">";
    }
    return 0;
}