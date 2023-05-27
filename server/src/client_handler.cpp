#include "client_handler.hpp"

QMap<int, QSet<int> > &ClientHandler::get_companies() {
    return companies;
}

QHash<QString, int> &ClientHandler::get_emails() {
    return clients_emails;
}

void ClientHandler::send_message_to_company(
    int company_id,
    const QJsonDocument &message
) {
    qDebug() << "sending data to company" << company_id;
    for (int socket_id : get_companies()[company_id]) {
        qDebug() << socket_id;
        get_clients()[socket_id]->send_data(message.toJson());
    }
};

void ClientHandler::move_to_companies(
    int socket_id,
    const QString &email,
    int company_id
) {
    qDebug() << "moving to companies";
    get_companies()[company_id].insert(socket_id);
    get_emails()[email] = socket_id;
}

void ClientHandler::send_message_to_array_of_users(
    const std::string &users,
    const QJsonDocument &message
) {
    std::string cur_email_to_send;
    std::stringstream ss(users);
    while (std::getline(ss, cur_email_to_send, '|')) {
        get_clients()[get_emails()[QString::fromStdString(cur_email_to_send)]]
            ->send_data(message.toJson());
    }
    qDebug() << message.object().value("emails_of_recipients").toString();
}

QMap<int, ClientSocket *> &ClientHandler::get_clients() {
    return connected_sockets;
}
