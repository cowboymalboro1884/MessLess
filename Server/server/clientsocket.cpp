#include <QJsonObject>
#include <QJsonParseError>

#include "server.h"


ClientSocket::ClientSocket(qintptr ID, QString client_id, Server *server_, QObject* parent)
    : QObject(parent),
      client_id(client_id),
      server(server_),
      socket_descriptor(ID)
{
    qDebug() << "client connected";

    socket = server->server->nextPendingConnection();

    connect(socket, SIGNAL(readyRead()), this, SLOT(readData(QByteArray&data)));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

QString ClientSocket::get_id() const {
    return client_id;
}

ClientSocket::~ClientSocket() {
    socket->deleteLater();
}


// TODO
void ClientSocket::readData(const QByteArray& data) {
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

        if (event_type == "authorization") {
           QJsonObject json = json_data.object();
           user_name = json.value("username").toString();
           entered_password = json.value("password").toString();
        }
    } else {
        QJsonObject jsonResponse;
        jsonResponse["type"] = "error";
        jsonResponse["text"] = "Invalid JSON";
        QJsonDocument doc(jsonResponse);
        sendData(doc.toJson());
    }
}

void ClientSocket::disconnected() {
    qDebug() << "disconnected";
    server->sockDisc(this);
}

void ClientSocket::sendData(QString data) {
  socket->flush();
}



