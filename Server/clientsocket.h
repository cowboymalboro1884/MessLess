#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QDebug>
#include <QJsonObject>
#include <QJsonParseError>
#include <QString>
#include <QTcpSocket>

class Server;

class ClientSocket : QObject {
    Q_OBJECT
public:
    explicit ClientSocket(
        qintptr ID,
        Server *server_,
        QTcpSocket *socket_,
        QObject *parent = nullptr
    );

    ~ClientSocket();

    void sendData(QString data);

    qint16 get_id() const;

    QTcpSocket *socket;
    bool isCheckSuccessfull = false;

public slots:
    void readData();

    void disconnected();

private:
    Server *server;
    qintptr socket_descriptor;

    QString user_name;
    QString entered_password;
};

#endif  // CLIENTSOCKET_H
