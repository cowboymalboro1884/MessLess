#include "include/socketwrapper.h"

namespace client::network {

SocketWrapper::SocketWrapper(QString ip_, qint16 port_) {
    m_socket_wrap = new QTcpSocket(this);
    ip = ip_;
    port = port_;
}

void SocketWrapper::connect () {
    m_socket_wrap->connectToHost(ip, port);
    if(m_socket_wrap->waitForConnected()){
        qDebug() << "Connected, i think...";
    }
}

void SocketWrapper::send_data(const QByteArray &data){
    m_socket_wrap->write(data);
    m_socket_wrap->waitForBytesWritten();
}

SocketWrapper::~SocketWrapper() {
    m_socket_wrap->deleteLater();
}

} // namespace client::network
