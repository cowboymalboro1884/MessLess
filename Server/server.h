#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <iostream>

using namespace boost::asio;
using ip::tcp;
using std::string;

namespace server {
class Server : private boost::noncopyable {
public:
    string read_(tcp::socket &socket);

    void send_(tcp::socket &socket, const string &message);
};
}  // namespace server

#endif  // SERVER_H
