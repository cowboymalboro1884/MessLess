#include "client_handler.hpp"

QMap<int, QSet<int> > &ClientHandler::get_companies() {
    return companies;
}

QHash<QString, int> &ClientHandler::get_emails() {
    return clients_emails;
}

void ClientHandler::move_to_companies(
    int socket_id,
    const QString &email,
    int company_id
) {
    qDebug() << "moving to companies";
    get_companies()[company_id].insert(socket_id);
    get_emails()[email] = socket_id;
}

void ClientHandler::send_to_concrete_user(
    const QString &email,
    const QJsonDocument &response
) {
    int user_id_to_send = get_emails()[email];
    get_clients()[user_id_to_send]->write_byte_data(response.toJson());
}

void ClientHandler::send_message_to_project_user_list(
    const QJsonArray &users,
    const QJsonDocument &message
) {
    for (const auto &obj : users) {
        get_clients()[get_emails()[obj["email"].toString()]]->write_byte_data(
            message.toJson()
        );
    }
    qDebug() << message.object().value("emails_of_recipients").toString();
}

void ClientHandler::send_message_to_company(
    int company_id,
    const QJsonDocument &message
) {
    qDebug() << "sending data to company" << company_id;
    for (int socket_id : get_companies()[company_id]) {
        qDebug() << socket_id;
        get_clients()[socket_id]->write_byte_data(message.toJson());
    }
};

QMap<int, ClientSocket *> &ClientHandler::get_clients() {
    return connected_sockets;
}
