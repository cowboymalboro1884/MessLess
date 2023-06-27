#include <QDataStream>
#include <sstream>
#include "include/socketwrapper.h"

namespace client::network {

SocketWrapper::SocketWrapper(QString ip_, qint16 port_) {
    m_socket_wrap = new QTcpSocket(this);
    ip = ip_;
    port = port_;
}

void SocketWrapper::connect_to_host() {
    m_socket_wrap->connectToHost(ip, port);
    if (m_socket_wrap->waitForConnected()) {
        qDebug() << "Connected, i think...";
        connect(m_socket_wrap, SIGNAL(readyRead()), this, SLOT(update()));
    } else {
        throw "Couldn't connect to host";
    }
}

void SocketWrapper::update() {
    qDebug() << "Got new data to update!";
    QByteArray block_size_bytes = m_socket_wrap->read(4);
    QDataStream size_stream(&block_size_bytes, QIODevice::ReadOnly);
    qint32 block_size;
    size_stream >> block_size;
    while (m_socket_wrap->bytesAvailable() < block_size) {
        m_socket_wrap->waitForReadyRead(1000);
    }
    QByteArray response = m_socket_wrap->read(block_size);

    emit ready_to_proccess_data(response);
}

bool SocketWrapper::send_data(const QByteArray &data) {
    m_socket_wrap->write(data);
    return m_socket_wrap->waitForBytesWritten();
}

SocketWrapper::~SocketWrapper() {
    m_socket_wrap->deleteLater();
}

}  // namespace client::network
