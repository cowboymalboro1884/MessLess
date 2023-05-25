#ifndef CLIENT_HANDLER_HPP
#define CLIENT_HANDLER_HPP

#include <QHash>
#include <QJsonDocument>
#include <QMap>
#include <QMutex>
#include <QTcpServer>

class ClientSocket;

namespace messless {
class PrivateUserInfo;
}
class Server;

class ClientHandler {
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
    void send_message_to_array_of_users(
        const std::vector<QString> &users,
        const QJsonDocument &message
    );

    void move_to_companies(int socket_id, const QString &email, int company_id);

    void send_message_to_array_of_users(
        const std::string &users,
        const QJsonDocument &message
    );
};

#endif  // CLIENT_HANDLER_HPP
