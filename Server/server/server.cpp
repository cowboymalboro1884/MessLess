#include "server.h"

Server::Server(qint16 port_, QObject *parent) :
    QObject(parent) {
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
    connected_client = server->nextPendingConnection();
    connect(connected_client, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connected_client->write("Hello from server!\n");
    qDebug() << "Connected";
}

void Server::sockReady() {

}

void Server::readyRead(){
    QByteArray mess = connected_client->readAll();
    QJsonObject json_data = QJsonDocument::fromJson(mess).object();
    qDebug() << "get data!";
    qDebug() << "username: " << json_data.value("username").toString();
    qDebug() << "password: " << json_data.value("password").toString();

};

/// TODO
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
    connected_client->deleteLater();
    server->deleteLater();
}

