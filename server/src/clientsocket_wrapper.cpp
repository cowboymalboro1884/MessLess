#include <QDataStream>
#include <QJsonObject>
#include <QJsonParseError>
#include "request_handler.hpp"
#include "server.hpp"

ClientSocket::ClientSocket(
    qintptr ID,
    Server *server_,
    QTcpSocket *socket_,
    messless::Database *db_,
    QObject *parent
)
    : QObject(nullptr),
      socket(socket_),
      server(server_),
      m_db(db_),
      m_socket_descriptor(ID) {
    qDebug() << "client" << ID << "connected";
    request_holder = new RequestHandler(m_db);
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

    QString event_type = json_responce.object().value("type").toString();
    QString status = json_responce.object().value("status").toString();
    int company_id = json_responce.object().value("company_id").toInt();
    QString email = json_responce.object().value("email").toString();
    QString recipient = json_responce.object().value("recipient").toString();

    if ((event_type == "got_status_of_authorization" ||
         event_type == "got_status_of_registration") &&
        (status == "success")) {
        server->client_handler->move_to_companies(get_id(), email, company_id);
    }

    if (recipient == "to company") {
        server->client_handler->send_message_to_company(
            company_id, json_responce
        );
    } else if (recipient == "to sender") {
        send_data(json_responce.toJson());
    } else if (recipient == "to concrete user") {
        qDebug() << "sending data to concrete user";
        qDebug() << json_responce;
        int user_id_to_send = server->client_handler->get_emails()[email];
        server->client_handler->get_clients()[user_id_to_send]->send_data(
            json_responce.toJson()
        );

    } else if (recipient == "to array of users") {
        server->client_handler->send_message_to_array_of_users(
            json_responce.object()
                .value("emails_of_recipients")
                .toString()
                .toStdString(),
            json_responce
        );
    } else {
        qDebug() << "ошибся, брат";
    }
}

void ClientSocket::disconnected() {
    qDebug() << "try to disconnect";
    server->sock_disc(this);
}

void ClientSocket::send_data(const QByteArray &response) {
    qDebug() << response.size() << (quint16)response.size();

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)response.size();
    out << response;
    socket->write(block);
    socket->flush();
}

qint16 ClientSocket::get_id() const {
    return m_socket_descriptor;
}
