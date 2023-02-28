#ifndef CPP_PROJECT_CLIENT_H
#define CPP_PROJECT_CLIENT_H

#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;
using ip::tcp;
using std::string;

namespace client {
struct TCPClient {
    string read_(tcp::socket &socket);
};
}  // namespace client

#endif  // CPP_PROJECT_CLIENT_H