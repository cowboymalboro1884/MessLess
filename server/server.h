#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include <QThread>
#include <QJsonDocument>
#include <QMap>
#include "clientsocket.h"
#include "database.h"

class Server : public QObject
{
    Q_OBJECT
    QVector<ClientSocket*> sockets;
    QByteArray Data;
    messless::Database *db;
    qint16 PORT;
    qint16 user_counter = 1;

public:
    ~Server();
    bool startServer(qint16 port, std::string &config_file);
    void sockReady();
    void sockDisc(ClientSocket*);
    bool connectToDatabase(std::string& config_file);

    static Server& getInstance() {
        static Server server;
        return server;
    };

    QTcpServer *server;

public slots:
    void incomingConnection();

// made a singleton
private:
    Server(QObject *parent = nullptr);
    Server(const Server& );
    Server& operator=(const Server&);
};

#endif // SERVER_H
