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
    QMap<qint32, ClientSocket *> sockets;
    QByteArray Data;
    messless::Database *db;
    qint16 PORT;

public:
    ~Server();
    bool startServer(qint16 port, std::string &config_file);
    void sockReady();
    void sockDisc(ClientSocket *);
    bool connectToDatabase(std::string &config_file);

    static Server &getInstance() {
        static Server server;
        return server;
    };

    QTcpServer *server;

public slots:
    void incomingConnection();

    // made a singleton
private:
    Server(QObject *parent = nullptr);
    Server(const Server &);
    Server &operator=(const Server &);
};

#endif  // SERVER_H
