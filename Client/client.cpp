#include "client.h"

namespace client {
string TCPClient::read_(tcp::socket &socket) {
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, "\n");
    string data = boost::asio::buffer_cast<const char *>(buf.data());
    return data;
}
}  // namespace client