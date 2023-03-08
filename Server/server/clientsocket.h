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
    explicit ClientSocket(qintptr ID, QString client_id, Server *server_, QObject *parent = nullptr);
    ~ClientSocket();
    void sendData(QString data);
    QString get_id() const;

public slots:
    void readData(const QByteArray& data);
    void disconnected();

private:
    QString client_id;
    Server *server;
    qintptr socket_descriptor;
    QTcpSocket *socket;

    QString user_name;
    QString entered_password;
};

#endif // CLIENTSOCKET_H
