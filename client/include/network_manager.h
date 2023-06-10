#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMainWindow>
#include <QMutex>
#include <QMutexLocker>
#include <QTcpSocket>
#include <QThread>
#include "socketwrapper.h"
namespace client{
struct Client;
}
using client::network::SocketWrapper;

struct NetworkManager : public QObject {
    Q_OBJECT

public:
    NetworkManager(client::Client *client_, const QString &ip_, int port_);
    ~NetworkManager();

    void run();

    client::Client *client;
    QMutex *socket_mutex;

    int port;
    QString ip;

    SocketWrapper* m_socket_wrap;
    ResponseHandler* m_response_handler;
    QuerySender* m_query_sender;
};

#endif// NETWORKMANAGER_H
