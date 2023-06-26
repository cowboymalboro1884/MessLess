#include "server.hpp"

Server::Server(QObject *parent)
    : QObject(parent){

      };

bool Server::start_server(qint16 port, std::string &config_file) {
    server = new QTcpServer(this);
    PORT = port;

    if (server->listen(QHostAddress::Any, PORT)) {
        qDebug() << "Listening port" << PORT << "...";
        qDebug() << "My ip " << server->serverAddress().toString();

        connect(
            server, SIGNAL(newConnection()), this, SLOT(incoming_connection())
        );

        if (connect_to_database(config_file)) {
            qDebug() << "Connected to database";
        } else {
            qDebug() << "Couldn't connect to database";
            return false;
        }
        client_handler = new ClientHandler(this);
    } else {
        qDebug() << "Couldn't start server";
        return false;
    }
    return true;
}

void Server::incoming_connection() {
    qDebug() << "New connection!";
    QTcpSocket *next_connection = server->nextPendingConnection();

    ClientSocket *connected_socket = new ClientSocket(
        next_connection->socketDescriptor(), this, next_connection, m_db
    );

    client_handler->get_clients()[connected_socket->get_id()] =
        connected_socket;
}

void Server::connect_to_client_handler(
    int socket_id,
    const QString &email,
    int company_id
) {
    ClientSocket *connected_socket = client_handler->get_clients()[socket_id];

    connect(
        connected_socket,
        SIGNAL(
            send_message_to_project_user_list(const QJsonArray &, const QJsonDocument &)
        ),
        client_handler,
        SLOT(
            send_message_to_project_user_list(const QJsonArray &, const QJsonDocument &)
        )
    );

    connect(
        connected_socket,
        SIGNAL(
            send_message_to_concrete_user(const QString &, const QJsonDocument &)
        ),
        client_handler,
        SLOT(
            send_message_to_concrete_user(const QString &, const QJsonDocument &)
        )
    );
    connect(
        connected_socket,
        SIGNAL(send_message_to_company(int, const QJsonDocument &)),
        client_handler,
        SLOT(send_message_to_company(int, const QJsonDocument &))
    );

    client_handler->move_to_companies(socket_id, email, company_id);
}

void Server::sock_disc(ClientSocket *socket) {
    client_handler->get_clients().erase(
        client_handler->get_clients().find(socket->get_id())
    );
    for (auto &company_set : client_handler->get_companies()) {
        auto it = company_set.find(socket->get_id());
        if (it != company_set.end()) {
            company_set.erase(it);
            break;
        }
    }

    delete socket;
}

bool Server::connect_to_database(const std::string &config_file) {
    std::ifstream input(config_file);
    std::string private_salt, connection_string;
    std::getline(input, connection_string);
    std::getline(input, private_salt);
    m_db = new messless::Database(connection_string, private_salt);
    return m_db->is_open();
}

Server::~Server() {
    for (auto &client : client_handler->get_clients()) {
        client->socket->deleteLater();
    }
    server->deleteLater();
    delete client_handler;
    delete m_db;
}
