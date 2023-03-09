#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QDebug>
#include <QJsonObject>
#include <QJsonParseError>
#include <QString>
#include <QTcpSocket>

#include "database.h"

class Server;

class ClientSocket : QObject {
    Q_OBJECT
public:
    explicit ClientSocket(qintptr ID, Server *server_, QTcpSocket* socket_, messless::Database *db_, QObject *parent = nullptr);
    ~ClientSocket();
    void sendData(QString data);
    qint16 get_id() const;
    QTcpSocket *socket;
    bool isCheckSuccessfull = false;
    QString user_role;
    QString email;
    QString password;

public slots:
    void readData();
    void disconnected();

private:
    messless::Database* db;
    Server *server;
    qintptr socket_descriptor;
};


#endif // CLIENTSOCKET_H
