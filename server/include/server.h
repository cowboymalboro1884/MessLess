#ifndef SERVER_H
#define SERVER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QMutex>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include "chatmanager.h"
#include "clientsocket.h"

class Server : public QObject {
    Q_OBJECT
    QMutex client_mutex;
    QMap<qint32, ClientSocket *> connected_sockets;
    messless::Database *m_db;
    qint16 PORT;

public:
    ~Server();
    bool start_server(qint16 port, std::string &config_file);
    void sockReady();
    void sock_disc(ClientSocket *);
    bool connect_to_database(std::string &config_file);
    void send_message_to_company(const qint32 id_company);
    QMap<qint32, ClientSocket *> &get_clients();
    ChatManager *chat_m;

    static Server &get_instance() {
        static Server server;
        return server;
    };

    QTcpServer *server;

public slots:
    void incoming_connection();

private:
    Server(QObject *parent = nullptr);
    Server(const Server &);
    Server &operator=(const Server &);
};

#endif  // SERVER_H
