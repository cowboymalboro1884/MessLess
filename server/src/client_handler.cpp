#include "client_handler.hpp"

QMap<int, QSet<int> > &ClientHandler::get_companies() {
    return companies;
}

QHash<QString, int> &ClientHandler::get_emails() {
    return clients_emails;
}

QMap<int, ClientSocket *> &ClientHandler::get_clients() {
    return connected_sockets;
}

void ClientHandler::move_to_companies(
    int socket_id,
    const QString &email,
    int company_id
) {
    get_companies()[company_id].insert(socket_id);
    get_emails()[email] = socket_id;
}

void ClientHandler::send_message_to_concrete_user(
    const QString &email,
    const QJsonDocument &response
) {
    if (get_emails()[email]) {
        int user_id_to_send = get_emails()[email];
        if (get_clients()[user_id_to_send]) {
            get_clients()[user_id_to_send]->write_byte_data(response.toJson());
        }
    }
}

void ClientHandler::send_message_to_project_user_list(
    const QJsonArray &users,
    const QJsonDocument &message
) {
    for (const auto &obj : users) {
        if (get_emails()[obj["email"].toString()]) {
            int socket_id = get_emails()[obj["email"].toString()];
            if (get_clients()[socket_id]) {
                get_clients()[socket_id]->write_byte_data(message.toJson());
            }
        }
    }
}

void ClientHandler::send_message_to_company(
    int company_id,
    const QJsonDocument &message
) {
    for (int socket_id : get_companies()[company_id]) {
        if (get_clients()[socket_id]) {
            get_clients()[socket_id]->write_byte_data(message.toJson());
        }
    }
};
