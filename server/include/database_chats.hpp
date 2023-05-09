#ifndef DATABASE_CHATS_HPP
#define DATABASE_CHATS_HPP
#include "database.hpp"

namespace messless {
class Message {
public:
    std::string text_message;
    std::string file_link;
    User sender;
};

class DatabaseChats {
public:
    static unsigned int
    get_company_id(Database &db, PrivateUserInfo &user_info);

    static unsigned int get_chat_id(
        Database &db,
        unsigned int company_id,
        unsigned int project_id
    );  // project_id is zero if it is company chat

    static bool send_message(
        Database &db,
        unsigned int chat_id,
        PrivateUserInfo& user,
        const std::string &message,
        const std::string &file_link
    );  // returns true if message sent

    static std::vector<Message> get_all_messages(Database &db, unsigned int chat_id);
};
}  // namespace messless
#endif
