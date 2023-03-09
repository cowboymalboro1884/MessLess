#include <QJsonObject>
#include <QJsonParseError>

#include "server.h"


ClientSocket::ClientSocket(qintptr ID, Server *server_, QTcpSocket* socket_, messless::Database *db_, QObject* parent)
    : QObject(parent),
      socket(socket_),
      db(db_),
      server(server_),
      socket_descriptor(ID)
{
    qDebug() << "client" << ID << "connected";

    connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

ClientSocket::~ClientSocket() {
    socket->deleteLater();
}

// TODO
void ClientSocket::readData() {
    QByteArray data = socket->readAll();
    QJsonParseError json_data_error;
    QJsonDocument json_data = QJsonDocument::fromJson(data, &json_data_error);

    if (json_data_error.errorString().toInt() == QJsonParseError::NoError) {
        QString event_type = json_data.object().value("type").toString();

        if (!event_type.size()) {
            QJsonObject jsonResponse;
            jsonResponse["type"] = "error";
            jsonResponse["text"] = "missing request type";
            QJsonDocument doc(jsonResponse);
            sendData(doc.toJson());
            return;
        }
        qDebug() << event_type;
        if (event_type == "authorization") {
           QJsonObject json = json_data.object();
           QString user_name = json.value("username").toString();
           QString entered_password = json.value("password").toString();
           qDebug() << "login: " << user_name;
           qDebug() << "password: " << entered_password;
        } else if (event_type == "registration") {
            QJsonObject json = json_data.object();
            qDebug() << "i'm here";
            messless::UserInfo user_info = messless::DatabaseCompany::create_user(*db, "email@jopa.com", "entered_password", "suka", "blyadskaya", 13, "admin");
        }
    } else {
        qDebug() << "smth wrong(";
        QJsonObject jsonResponse;
        jsonResponse["type"] = "error";
        jsonResponse["text"] = "Invalid JSON";
        QJsonDocument doc(jsonResponse);
        sendData(doc.toJson());
    }
}

void ClientSocket::disconnected() {
    server->sockDisc(this);
}


void ClientSocket::sendData(QString data) {
  socket->flush();
}

qint16 ClientSocket::get_id() const {
    return socket_descriptor;
}
