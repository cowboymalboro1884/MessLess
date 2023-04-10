#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QDebug>
#include <QJsonObject>
#include <QJsonParseError>
#include <QString>
#include <QTcpSocket>
#include "database.h"
#include "requestholder.h"

class Server;

class ClientSocket : QObject {
    Q_OBJECT
public:
    explicit ClientSocket(
        qintptr ID,
        Server *server_,
        QTcpSocket *socket_,
        messless::Database *db_,
        QObject *parent = nullptr
    );
    ~ClientSocket();
    void sendData(const QByteArray &data);
    qint16 get_id() const;
    QTcpSocket *socket;
    bool isCheckSuccessfull = false;

    RequestHolder *holder;

    QString user_role;
    QString email;
    QString password;

public slots:
    void readData();
    void disconnected();

private:
    messless::Database *db;
    Server *server;
    qintptr socket_descriptor;
};

#endif  // CLIENTSOCKET_H
