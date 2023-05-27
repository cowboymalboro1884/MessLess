#include "request_handler.hpp"

using namespace templates::ResponseTemplate;

QJsonArray RequestHandler::get_raw_chat(int company_id, int project_id)
    const noexcept {  // DONE
    unsigned int chat_id =
        messless::DatabaseChats::get_chat_id(*database, company_id, project_id);

    std::vector<messless::Message> messages_to_send =
        messless::DatabaseChats::get_all_messages(*database, chat_id);

    QJsonArray raw_chat;
    for (const auto &message : messages_to_send) {
        QJsonObject message_object;
        message_object["name_of_sender"] =
            QString::fromStdString(message.sender.name);
        message_object["surname_of_sender"] =
            QString::fromStdString(message.sender.surname);
        message_object["user_role_of_sender"] =
            QString::fromStdString(message.sender.user_role);

        message_object["message_text"] =
            QString::fromStdString(message.text_message);
        message_object["file_link"] = QString::fromStdString(message.file_link);
        raw_chat.append(message_object);
    }

    return raw_chat;
}

QJsonDocument RequestHandler::send_message_to_company(const QJsonObject &request
) const {  // DONE
    qDebug() << "----------------------------\ngot for send message";

    messless::PrivateUserInfo sender = extract_user_info_from_qjson(request);

    std::string message = request.value("message").toString().toStdString();
    std::string file_link = request.value("file_link").toString().toStdString();
    const unsigned int TO_COMPANY = 0;

    unsigned int company_id =
        messless::DatabaseChats::get_company_id(*database, sender);
    unsigned int chat_id =
        messless::DatabaseChats::get_chat_id(*database, company_id, TO_COMPANY);

    messless::DatabaseChats::send_message(
        *database, chat_id, sender, message, file_link
    );

    messless::User sender_user =
        messless::DatabaseChats::from_private_user_info_to_user(
            *database, sender
        );

    RecievedMessageResponse response(
        sender_user.name, sender_user.surname, sender.user_role, message,
        file_link, company_id
    );

    return response.to_qjson_document();
}

QJsonDocument RequestHandler::send_message_to_project(const QJsonObject &request
) const {  // DONE
    qDebug() << "----------------------------\ngot for send message";

    messless::PrivateUserInfo sender = extract_user_info_from_qjson(request);

    std::string message = request.value("message").toString().toStdString();
    std::string file_link = request.value("file_link").toString().toStdString();

    std::string project_name =
        request.value("project_name").toString().toStdString();

    unsigned int company_id =
        messless::DatabaseChats::get_company_id(*database, sender);

    int project_id = messless::DatabaseProject::get_project_id(
        *database, sender, project_name
    );

    unsigned int chat_id =
        messless::DatabaseChats::get_chat_id(*database, company_id, project_id);

    messless::DatabaseChats::send_message(
        *database, chat_id, sender, message, file_link
    );

    messless::User sender_user =
        messless::DatabaseChats::from_private_user_info_to_user(
            *database, sender
        );

    RecievedMessageResponse response(
        sender_user.name, sender_user.surname, sender_user.user_role, message,
        file_link, company_id
    );

    std::vector<messless::User> user_list =
        messless::DatabaseProject::get_project_user_list(*database, project_id);

    QJsonArray recipients;

    for (const auto &user : user_list) {
        QJsonObject email;
        email["email"] = QString::fromStdString(user.email);
        recipients.append(email);
    }
    response.change_to_project_chat(
        recipients, QString::fromStdString(project_name)
    );

    return response.to_qjson_document();
}
