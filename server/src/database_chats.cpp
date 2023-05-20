#include "../include/database_chats.hpp"

namespace messless {

unsigned int
DatabaseChats::get_company_id(Database &db, PrivateUserInfo &user_info) {
    try {
        pqxx::work worker(db.connection);
        unsigned int company_id = worker.query_value<int>(
            "SELECT company_id FROM users "
            "WHERE email='" +
            db.shield_string(user_info.email) + "';"
        );
        worker.commit();
        return company_id;
    } catch (...) {
        return 0;
    }
}

unsigned int DatabaseChats::get_chat_id(
    Database &db,
    unsigned int company_id,
    unsigned int project_id
) {
    try {
        pqxx::work worker(db.connection);
        unsigned int chat_id = worker.query_value<int>(
            "SELECT id FROM chats "
            "WHERE company_id=" +
            db.shield_string(std::to_string(company_id)) +
            " AND project_id=" + db.shield_string(std::to_string(project_id))+";"
        );
        worker.commit();
        return chat_id;
    } catch (...) {
        return 0;
    }
}

bool DatabaseChats::send_message(
    Database &db,
    unsigned int chat_id,
    PrivateUserInfo& user,
    const std::string &message,
    const std::string &file_link
) {
    try {
        pqxx::work worker(db.connection);
        unsigned int user_id = worker.query_value<int>(
            "SELECT id FROM users WHERE email='" +
            db.shield_string(user.email) + "';"
        );
        std::cout<<user_id<<'\n'
        worker.exec(
            "INSERT into messages (chat_id,text_message,sender_id,file_link) VALUES(" +
            db.shield_string(std::to_string(chat_id)) + ",'" +
            db.shield_string(message) + "',"+ db.shield_string(std::to_string(user_id))+",'"+db.shield_string(file_link)+"');"
        );
        worker.commit();
        return true;
    }
    catch(...){
        return false;
    }
}

std::vector<Message>
DatabaseChats::get_all_messages(Database &db, unsigned int chat_id) {
    std::vector<Message> messages;
    pqxx::work worker(db.connection);
    pqxx::result res = worker.exec(
        "SELECT text_message, file_link, sender_id FROM projects WHERE chat_id=" +
        db.shield_string(std::to_string(chat_id)) + ";"
    );
    for (auto row: res){
        std::string text_message = row[0].c_str();
        std::string file_link = row[1].c_str();
        unsigned int user_id = std::stoi(row[2].c_str());
        User current_user;
        current_user.email = worker.query_value<std::string>(
            "SELECT email FROM users WHERE id=" +
            db.shield_string(std::to_string(user_id)) + ";"
        );
        current_user.name = worker.query_value<std::string>(
            "SELECT first_name FROM users WHERE id=" +
            db.shield_string(std::to_string(user_id)) + ";"
        );
        current_user.surname = worker.query_value<std::string>(
            "SELECT second_name FROM users WHERE id=" +
            db.shield_string(std::to_string(user_id)) + ";"
        );
        messages.push_back({text_message,file_link,current_user});
    }
    worker.commit();
    return messages;
}

}  // namespace messless
