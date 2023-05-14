#ifndef CHATMANAGER_H
#define CHATMANAGER_H

#include <QJsonDocument>
#include <QMutex>

class ClientSocket;

namespace messless {
class PrivateUserInfo;
}
class Server;

class ChatManager {
    Server *owner;
    QMutex chat_mutex;
    void save_message_to_database(
        messless::PrivateUserInfo sender,
        const std::string &message
    );

public:
    ChatManager();
    void send_message_to_company(
        const QJsonDocument message,
        messless::PrivateUserInfo sender_info
    );
};

#endif  // CHATMANAGER_H
