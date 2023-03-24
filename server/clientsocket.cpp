#include <QJsonObject>
#include <QJsonParseError>

#include "server.h"

ClientSocket::ClientSocket(qintptr ID, Server *server_, QTcpSocket *socket_,
                           messless::Database *db_, QObject *parent)
    : QObject(nullptr), socket(socket_), db(db_), server(server_),
      socket_descriptor(ID) {
  qDebug() << "client" << ID << "connected";

  holder = new RequestHolder(db);
  connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));
  connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

ClientSocket::~ClientSocket() { socket->deleteLater(); }

void ClientSocket::readData() {
  QByteArray data = socket->readAll();
  QJsonDocument json_responce = holder->proccessData(data);
  sendData(json_responce.toJson());
}

void ClientSocket::disconnected() { server->sockDisc(this); }

void ClientSocket::sendData(const QByteArray &response) {
  socket->write(response);
  socket->flush();
}

qint16 ClientSocket::get_id() const { return socket_descriptor; }
