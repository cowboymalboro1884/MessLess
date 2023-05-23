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

    if((json_responce["type"] == "got_status_of_authorization" ||
            json_responce["type"] == "got_status_of_registration") &&
            (json_responce["status"] == "success")) {
        qDebug() << "moving to companies";
        server->get_companies()[json_responce.object().value("company_id").toInt()].insert(get_id());
        server->get_emails()[json_responce.object().value("email").toString()] = get_id();
    }
    qDebug() << "aboba" << json_responce.object().value("company_id").toString();
    if(json_responce.object().value("recipient").toString() == "to company") {
        int company_id = json_responce.object().value("company_id").toString().toInt();
        qDebug() << "sending data to company" << company_id;
        qDebug() << server->get_companies()[json_responce.object().value("company_id").toInt()].empty();
        for(auto socket_id : server->get_companies()[json_responce.object().value("company_id").toInt()]){
            qDebug() << "socket: " << socket_id;
        }
        server->send_message_to_company(company_id, json_responce);
    } else if (json_responce.object().value("recipient").toString() == "to sender") {
        qDebug() << "sending data to user";
        qDebug() << json_responce;
        send_data(json_responce.toJson());
    } else if (json_responce.object().value("recipient").toString() == "to concrete user") {
        qDebug() << "sending data to concrete user";
        qDebug() << json_responce;
        qint32 user_id_to_send = server->get_emails()[json_responce.object().value("email").toString()];
        server->get_clients()[user_id_to_send]->send_data(json_responce.toJson());
    } else {
        qDebug() << json_responce.object().value("recipient").toString();
        qDebug() << "ошибся, брат";
    }
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
