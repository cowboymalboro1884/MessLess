#ifndef SERVER_H
#define SERVER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "clientsocket.h"

class Server : public QObject {
    Q_OBJECT
    QVector<ClientSocket *> sockets;
    QByteArray Data;
    qint16 PORT;
    qint16 user_counter = 1;

public:
    explicit Server(qint16 port, QObject *parent = nullptr);
    ~Server();
    QTcpServer *server;
    void startServer();
    void sockReady();
    void sockDisc(ClientSocket *);

public slots:
    void incomingConnection();
};

#endif  // SERVER_H
