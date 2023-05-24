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

    QString event_type = json_responce.object().value("type").toString();
    QString status = json_responce.object().value("status").toString();
    int company_id = json_responce.object().value("company_id").toInt();
    QString email = json_responce.object().value("email").toString();
    QString recipient = json_responce.object().value("recipient").toString();

    if((event_type == "got_status_of_authorization" ||
        event_type == "got_status_of_registration") &&
        (status == "success")) {
        qDebug() << "moving to companies";
        server->get_companies()[company_id].insert(get_id());
        server->get_emails()[email] = get_id();
    }
    qDebug() << "company_id:" << email;

    if(recipient == "to company") {
        qDebug() << "sending data to company" << company_id;
        qDebug() << server->get_companies()[company_id].empty();
        for(auto socket_id : server->get_companies()[company_id]){
            qDebug() << "sending to socket: " << socket_id;
        }
        server->send_message_to_company(company_id, json_responce);
    } else if (recipient == "to sender") {
        qDebug() << "sending data to user";
        qDebug() << json_responce;
        send_data(json_responce.toJson());
    } else if (recipient == "to concrete user") {
        qDebug() << "sending data to concrete user";
        qDebug() << json_responce;
        int user_id_to_send = server->get_emails()[email];
        server->get_clients()[user_id_to_send]->send_data(json_responce.toJson());
    } else if(recipient == "to array of users"){
        std::string cur_email_to_send;
        std::stringstream ss(json_responce.object().value("emails_of_recipients").toString().toStdString());
        while(std::getline(ss, cur_email_to_send, '|')) {
             server->get_clients()[server->get_emails()[QString::fromStdString(cur_email_to_send)]]->\
                     send_data(json_responce.toJson());
        }
        qDebug() << json_responce.object().value("emails_of_recipients").toString();
    }else{
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
