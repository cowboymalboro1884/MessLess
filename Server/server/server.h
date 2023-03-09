#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include "clientsocket.h"
#include "database.h"

class Server : public QObject
{
    Q_OBJECT
    QVector<ClientSocket*> sockets;
    QByteArray Data;
    messless::Database *db;
    qint16 PORT;
    qint16 user_counter = 1;

public:
    explicit Server(qint16 port, messless::Database *db, QObject *parent = nullptr);
    ~Server();
    QTcpServer *server;
    void startServer();
    void sockReady();
    void sockDisc(ClientSocket*);

public slots:
    void incomingConnection();
};

#endif // SERVER_H
