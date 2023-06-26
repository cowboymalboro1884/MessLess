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
        int company_id,
        RSAKeys keys
) {
    qDebug() << "moving to companies";
    get_companies()[company_id].insert(socket_id);
    qDebug() << company_id << ' ' << socket_id;
    get_emails()[email] = socket_id;
    get_encrypting_keys()[socket_id] = keys;
}

QMap<int, RSAKeys> &ClientHandler::get_encrypting_keys() {
    return encrypting_keys;
}

void ClientHandler::send_message_to_concrete_user(
        const QString &email,
        const QJsonDocument &response
) {
    int user_id_to_send = get_emails()[email];
    
    std::string encrypted_message_text = Encrypting::encrypt(
            response.object()["message_text"].toString().toStdString(), get_encrypting_keys()[user_id_to_send].PublicKey);
    response.object()["message_text"] = QString::fromStdString(encrypted_message_text);
    
    get_clients()[user_id_to_send]->write_byte_data(response.toJson());
}

void ClientHandler::send_message_to_project_user_list(
        const QJsonArray &users,
        const QJsonDocument &message
) {
    for (const auto &obj: users) {
        qDebug() << obj["email"].toString();
        int socket_id = get_emails()[obj["email"].toString()];
        
        
        std::string encrypted_message_text = Encrypting::encrypt(
                message.object()["message_text"].toString().toStdString(), get_encrypting_keys()[socket_id].PublicKey);
        message.object()["message_text"] = QString::fromStdString(encrypted_message_text);
        
        get_clients()[socket_id]->write_byte_data(
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
    for (int socket_id: get_companies()[company_id]) {
        qDebug() << socket_id;
        std::string encrypted_message_text = Encrypting::encrypt(
                message.object()["message_text"].toString().toStdString(), get_encrypting_keys()[socket_id].PublicKey);
        message.object()["message_text"] = QString::fromStdString(encrypted_message_text);
        get_clients()[socket_id]->write_byte_data(message.toJson());
    }
};

QMap<int, ClientSocket *> &ClientHandler::get_clients() {
    return connected_sockets;
}
