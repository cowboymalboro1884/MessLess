#ifndef SOCKETWRAPPER_H
#define SOCKETWRAPPER_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

namespace client::network {
class SocketWrapper : public QObject {
    Q_OBJECT
    QTcpSocket* m_socket_wrap;
    QString ip;
    qint16 port;

public:
    SocketWrapper(QString ip, qint16 port);
    ~SocketWrapper();

    void connect();
    void send_data(const QByteArray &data);
};
} // namespace client::web

#endif // SOCKETWRAPPER_H
