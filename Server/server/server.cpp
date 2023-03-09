#include "server.h"

Server::Server(qint16 port_, messless::Database *db_,QObject *parent) :
    QObject(parent) {
    db = db_;
    server = new QTcpServer(this);
    PORT = port_;
};

void Server::startServer() {
    if(server->listen(QHostAddress::Any, PORT)){
        qDebug() << "Listening port" << PORT << "...";
        qDebug() << "My ip " << server->serverAddress().toString();

        connect(server, SIGNAL(newConnection()), this, SLOT(incomingConnection()));
    } else {
        qDebug() << "Couldn't start server";
    }
}

void Server::incomingConnection() {
    qDebug() << "New connection!";
    ClientSocket* connected_socket = new ClientSocket(user_counter, this, server->nextPendingConnection(), db);
    sockets.push_back(connected_socket);
    user_counter++;
    connected_socket->socket->write("Hello from server!\n");
}

void Server::sockDisc(ClientSocket* socket) {
    qDebug() << "Disconnected" << socket->get_id();

    for(int i = 0; i < sockets.size(); i++){
        if(socket == sockets[i]) {
            delete sockets[i];
            sockets.removeAt(i);
            break;
        }
    }
}

Server::~Server() {
    for(auto &client: sockets){
        client->socket->deleteLater();
    }
    server->deleteLater();
}

