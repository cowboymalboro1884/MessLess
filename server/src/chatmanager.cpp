#include "server.h"

void ChatManager::send_message_to_company(
    const QJsonDocument message,
    messless::PrivateUserInfo sender_info
) {
    std::string message_to_send =
        message.object().value("message").toString().toStdString();
    save_message_to_database(sender_info, message_to_send);
    for (auto &client : owner->get_clients()) {
        client->send_data(message.toJson());
    }
}

void ChatManager::save_message_to_database(
    messless::PrivateUserInfo sender,
    const std::string &message
) {
    //... андрей работай блять
}
