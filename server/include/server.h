#ifndef SERVER_H
#define SERVER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QMutex>
#include <memory>
#include "clientsocket.h"
#include "chatmanager.h"

class Server : public QObject {
    Q_OBJECT

    QMutex client_mutex;
    QMap<qint32, ClientSocket *> connected_sockets;
    QMap<qint32, QSet<qint32> > companies;
    QHash<QString, qint32> clients_emails;
    messless::Database *m_db;
    qint16 PORT;

public:
    ~Server();
    bool start_server(qint16 port, std::string &config_file);
    void sockReady();
    void sock_disc(ClientSocket *);
    bool connect_to_database(std::string &config_file);

    void send_message_to_company(const qint32 id_company, const QJsonDocument& message);
    void send_message_to_array_of_users(const std::vector<QString>& users, const QJsonDocument& message);

    QMap<qint32, ClientSocket *>& get_clients(); // socket_id --> clientsocket*
    QMap<qint32, QSet<qint32> >& get_companies();  // company_id --> set of socket_id
    QHash<QString, qint32>& get_emails();
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
