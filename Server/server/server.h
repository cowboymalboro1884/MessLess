#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include "clientsocket.h"

class Server : public QObject
{
    Q_OBJECT
    QVector<ClientSocket*> sockets;
    QByteArray Data;
    qint16 PORT;
    QTcpSocket* connected_client;

public:
    explicit Server(qint16 port, QObject *parent = nullptr);
    ~Server();
    QTcpServer *server;
    void startServer();
    void sockReady();
    void sockDisc(ClientSocket*);

public slots:
    void incomingConnection();
    void readyRead();
};


#endif // SERVER_H
