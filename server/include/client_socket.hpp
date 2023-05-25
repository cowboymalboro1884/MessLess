#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QDebug>
#include <QJsonObject>
#include <QJsonParseError>
#include <QString>
#include <QTcpSocket>
#include "request_handler.hpp"

class Server;

class ClientSocket : QObject {
    Q_OBJECT
public:
    explicit ClientSocket(
        qintptr ID,
        Server *m_server,
        QTcpSocket *m_socket,
        messless::Database *m_db,
        QObject *parent = nullptr
    );
    ~ClientSocket();

    qint16 get_id() const;
    QTcpSocket *socket;
    RequestHolder *request_holder;
    Server *server;

    void send_data(const QByteArray &data);

public slots:
    void read_data();
    void disconnected();

private:
    messless::Database *m_db;
    qintptr m_socket_descriptor;
};

#endif  // CLIENTSOCKET_H
