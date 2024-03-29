#include <QDataStream>
#include <QJsonObject>
#include <QJsonParseError>
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
    QJsonDocument json_response = request_holder->proccess_data(data);
    send_json_data(json_response);
}

void ClientSocket::disconnected() {
    qDebug() << "Disconnected";
    server->sock_disc(this);
}

void ClientSocket::send_json_data(const QJsonDocument &json_response) {
    QString event_type = json_response.object()["type"].toString();
    QString status = json_response.object()["status"].toString();
    int company_id = json_response.object()["company_id"].toInt();
    QString email = json_response.object()["email"].toString();
    int recipient = json_response.object()["recipient"].toInt();
    qDebug() << event_type;
    if ((event_type == response_types[GOT_STATUS_OF_AUTHORIZATION] ||
         event_type == response_types[GOT_STATUS_OF_REGISTRATION]) &&
        (status == "success")) {

        server->connect_to_client_handler(get_id(), email, company_id);
    }

    switch (recipient) {
        case TO_COMPANY: {
            emit send_message_to_company(company_id, json_response);
            break;
        }
        case TO_SENDER: {
            write_byte_data(json_response.toJson());
            break;
        }
        case TO_PROJECT_USER_LIST: {
            emit send_message_to_project_user_list(
                json_response.object()["emails_of_recipients"].toArray(), json_response
            );
            break;
        }
        case TO_CONCRETE_USER: {
            QString reciever_email = json_response.object()["reciever_email"].toString();
            emit send_message_to_concrete_user(reciever_email, json_response);
            break;
        }
        default:
            qDebug() << "Invalid recipient";
    }
}

void ClientSocket::write_byte_data(const QByteArray &response) {
    QByteArray block_size;
    QDataStream out(&block_size, QIODevice::WriteOnly);
    out << quint32(response.size());
    socket->write(block_size);

    socket->write(response);
    socket->flush();
}

qint16 ClientSocket::get_id() const {
    return m_socket_descriptor;
}
