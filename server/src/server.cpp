#include "server.h"

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
    } else {
        qDebug() << "Couldn't start server";
        return false;
    }
    return true;
}

void Server::incoming_connection() {
    qDebug() << "New connection!";
    QTcpSocket *next_connection = server->nextPendingConnection();
    qDebug() << m_db->connection.is_open() << "connection";
    ClientSocket *connected_socket = new ClientSocket(
        next_connection->socketDescriptor(), this, next_connection, m_db
    );
    get_clients()[connected_socket->get_id()] = connected_socket;
}

void Server::sock_disc(ClientSocket *socket) {
    client_mutex.lock();

    get_clients().erase(connected_sockets.find(socket->get_id()));
    delete socket;
    client_mutex.unlock();
}

bool Server::connect_to_database(std::string &config_file) {
    std::ifstream input(config_file);
    std::string private_salt, connection_string;
    std::getline(input, connection_string);
    std::getline(input, private_salt);
    m_db = new messless::Database(connection_string, private_salt);
    return m_db->connection.is_open();
}

QMap<qint32, ClientSocket *>& Server::get_clients() {
    return connected_sockets;
}

QMap<qint32, QSet<qint32> >& Server::get_companies() {
    return companies;
}

void Server::send_message_to_company(const qint32 id_company, const QJsonDocument& message){
    for(qint32 socket_id : get_companies()[id_company]) {
        get_clients()[socket_id]->send_data(message.toJson());
    }
};

Server::~Server() {
    for (auto &client : connected_sockets) {
        client->socket->deleteLater();
    }
    server->deleteLater();
    delete chat_m;
    delete m_db;
}
