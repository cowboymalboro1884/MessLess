#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QDebug>
#include <QJsonObject>
#include <QJsonParseError>
#include <QString>
#include <QTcpSocket>
#include "request_handler.hpp"

class Server;

class ClientSocket : public QObject {
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
    RequestHandler *request_holder;
    Server *server;

    void write_byte_data(const QByteArray &data);
    void send_json_data(const QJsonDocument &data);

public slots:
    void read_data();
    void disconnected();

signals:
    void
    send_message_to_project_user_list(const QJsonArray &, const QJsonDocument &);
    void send_message_to_concrete_user(const QString &, const QJsonDocument &);
    void send_message_to_company(int, const QJsonDocument &);

private:
    messless::Database *m_db;
    qintptr m_socket_descriptor;
};

#endif  // CLIENTSOCKET_H
