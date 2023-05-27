#ifndef CLIENT_HANDLER_HPP
#define CLIENT_HANDLER_HPP

#include <QHash>
#include <QJsonDocument>
#include <QMap>
#include <QMutex>
#include <QTcpServer>
#include <iostream>
#include <sstream>
#include "clientsocket_wrapper.hpp"

class ClientSocket;

namespace messless {
class PrivateUserInfo;
}
class Server;

class ClientHandler : public QObject {
    Server *owner;

    QMap<int, QSet<int> > companies;
    QHash<QString, int> clients_emails;
    QMap<int, ClientSocket *> connected_sockets;

public:
    ClientHandler(Server *owner_) : owner(owner_){};

    QMap<int, QSet<int> > &get_companies();
    QHash<QString, int> &get_emails();
    QMap<int, ClientSocket *> &get_clients();

    void send_message_to_company(
        const qint32 id_company,
        const QJsonDocument &message
    );

public slots:
    void
    send_to_concrete_user(const QString &, const QJsonDocument &);

    void send_message_to_project_user_list(
        const QJsonArray &users,
        const QJsonDocument &response
    );

    void move_to_companies(int socket_id, const QString &email, int company_id);
};

#endif  // CLIENT_HANDLER_HPP
