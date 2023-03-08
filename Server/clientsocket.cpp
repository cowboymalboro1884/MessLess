#include <QJsonObject>
#include <QJsonParseError>
#include "server.h"

ClientSocket::ClientSocket(
    qintptr ID,
    Server *server_,
    QTcpSocket *socket_,
    QObject *parent
)
    : QObject(parent), socket(socket_), server(server_), socket_descriptor(ID) {
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

        if (event_type == "authorization") {
            QJsonObject json = json_data.object();
            user_name = json.value("username").toString();
            entered_password = json.value("password").toString();
            qDebug() << json;
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
    server->sockDisc(this);
}

void ClientSocket::sendData(QString data) {
    socket->flush();
}

qint16 ClientSocket::get_id() const {
    return socket_descriptor;
}
