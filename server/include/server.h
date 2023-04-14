#ifndef SERVER_H
#define SERVER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include "clientsocket.h"
#include "database.h"

class Server : public QObject {
    Q_OBJECT
    QMap<qint32, ClientSocket *> connected_sockets;
    messless::Database *m_db;
    qint16 PORT;

public:
    ~Server();
    bool start_server(qint16 port, std::string &config_file);
    void sockReady();
    void sock_disc(ClientSocket *);
    bool connect_to_database(std::string &config_file);

    static Server &get_instance() {
        static Server server;
        return server;
    };

    QTcpServer *server;

public slots:
    void incoming_connection();

    // made a singleton
private:
    Server(QObject *parent = nullptr);
    Server(const Server &);
    Server &operator=(const Server &);
};

#endif  // SERVER_H
