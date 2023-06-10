#ifndef SOCKETWRAPPER_H
#define SOCKETWRAPPER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QTcpSocket>
#include "query_handler.h"
#include "response_types.h"


namespace client::network {

struct SocketWrapper : public QObject {
    Q_OBJECT
    QTcpSocket *m_socket_wrap;
    QString ip;
    qint16 port;

public:
    SocketWrapper(QString ip, qint16 port);
    ~SocketWrapper();

    void connect_to_host();

signals:
    void ready_to_proccess_data(const QByteArray&);

public slots:
    void update();
    bool send_data(const QByteArray &data);
};
}  // namespace client::network

#endif  // SOCKETWRAPPER_H
