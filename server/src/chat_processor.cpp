#include "request_handler.hpp"

using namespace templates::ResponseTemplate;

QJsonDocument RequestHandler::send_message_to_company(const QJsonObject &request
) const {
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

    ChatResponse json_response("got_new_message_to_company");
    json_response.set_message(QString::fromStdString(message));
    json_response.set_recipient("to company");
    json_response.set_status("success");
    json_response.set_company_id(company_id);

    json_response.set_name_of_sender(QString::fromStdString(sender_user.name));
    json_response.set_surname_of_sender(
        QString::fromStdString(sender_user.surname)
    );

    json_response.set_user_role(QString::fromStdString(sender_user.user_role));
    json_response.set_file_link(QString::fromStdString(file_link));

    return json_response.to_qjson_document();
}

QJsonDocument RequestHandler::send_message_to_project(const QJsonObject &request
) const {
    // TODO
}

QJsonDocument RequestHandler::get_company_chat(const QJsonObject &request
) const {
    // TODO
};

QJsonDocument RequestHandler::get_project_chat(const QJsonObject &request
) const {
    // TODO
};
