#ifndef SERVER_H
#define SERVER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QMutex>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <memory>
#include "client_handler.hpp"
#include "client_socket.hpp"
#include "response_template.hpp"

class Server : public QObject {
    Q_OBJECT

    messless::Database *m_db;
    qint16 PORT;

public:
    static Server &get_instance() {
        static Server server;
        return server;
    };

    ~Server();

    bool start_server(qint16 port, std::string &config_file);
    void sockReady();
    void sock_disc(ClientSocket *);
    bool connect_to_database(const std::string &config_file);

    ClientHandler *client_handler;
    QTcpServer *server;

public slots:
    void incoming_connection();

private:
    Server(QObject *parent = nullptr);
    Server(const Server &);
    Server &operator=(const Server &);
};

#endif  // SERVER_H
