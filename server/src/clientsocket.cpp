#include <QJsonObject>
#include <QJsonParseError>
#include "server.h"
#include "requestholder.h"

ClientSocket::ClientSocket(
    qintptr ID,
    Server *server_,
    QTcpSocket *socket_,
    messless::Database* db_,
    QObject *parent
)
    : QObject(nullptr),
      socket(socket_),
      server(server_),
      m_db(db_),
      m_socket_descriptor(ID) {
    qDebug() << "client" << ID << "connected";
    request_holder = new RequestHolder(m_db);
    connect(socket, SIGNAL(readyRead()), this, SLOT(read_data()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

ClientSocket::~ClientSocket() {
    qDebug() << "Disconnected" << get_id();
    socket->deleteLater();
}

void ClientSocket::read_data() {
    QByteArray data = socket->readAll();
    QJsonDocument json_responce = request_holder->proccess_data(data);
    qDebug() << "sending data to socket";
    qDebug() << json_responce;
    send_data(json_responce.toJson());
}

void ClientSocket::disconnected() {
    qDebug() << "try to disconnect";
    server->sock_disc(this);
}

void ClientSocket::send_data(const QByteArray &response) {
    socket->write(response);
    socket->flush();
}

qint16 ClientSocket::get_id() const {
    return m_socket_descriptor;
}
