#include "server.h"

Server::Server(QObject *parent)
    : QObject(parent){

      };

bool Server::startServer(qint16 port, std::string &config_file) {
  server = new QTcpServer(this);
  PORT = port;

  if (server->listen(QHostAddress::Any, PORT)) {
    qDebug() << "Listening port" << PORT << "...";
    qDebug() << "My ip " << server->serverAddress().toString();

    connect(server, SIGNAL(newConnection()), this, SLOT(incomingConnection()));

    try {
      connectToDatabase(config_file);
      qDebug() << "Connected to database";
    } catch (...) {
      qDebug() << "Couldn't connect to database";
      return false;
    }
  } else {
    qDebug() << "Couldn't start server";
    return false;
  }
  return true;
}

void Server::incomingConnection() {
  qDebug() << "New connection!";
  QTcpSocket *next_connection = server->nextPendingConnection();
  ClientSocket *connected_socket = new ClientSocket(
      next_connection->socketDescriptor(), this, next_connection, db);
  sockets[connected_socket->get_id()] = connected_socket;
}

void Server::sockDisc(ClientSocket *socket) {
  qDebug() << "Disconnected" << socket->get_id();
  sockets.erase(sockets.find(socket->get_id()));
}

void Server::connectToDatabase(std::string &config_file) {
  std::ifstream input(config_file);
  std::string private_salt, connection_string;
  std::getline(input, connection_string);
  std::getline(input, private_salt);
  messless::Database db_(connection_string, private_salt);
  db = &db_;
}

Server::~Server() {
  for (auto &client : sockets) {
    client->socket->deleteLater();
  }
  server->deleteLater();
  delete db;
}
