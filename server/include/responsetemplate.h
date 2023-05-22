#ifndef RESPONSETEMPLATE_H
#define RESPONSETEMPLATE_H

#include <QJsonObject>
#include <QJsonDocument>

namespace templates::ResponseTemplate{

struct Response {
    QString event_type;
    QString status;
    QString recipient;
    QString error_text;

    QJsonObject main_data;

    Response(const QString& event_type_)
        : event_type(std::move(event_type_)) {};

    void set_status(const QString& status_) {
        status = std::move(status_);
    }

    void set_error_text(const QString& error_text_) {
        error_text = std::move(error_text_);
    }

    void set_recipient(const QString& recipient_) {
        recipient = std::move(recipient_);
    }

    virtual QJsonDocument to_qjson_document() {
        main_data["type"] = event_type;
        main_data["status"] = status;
        main_data["error_text"] = error_text;
        main_data["recipient"] = recipient;
        return QJsonDocument(main_data);
    };

    virtual bool is_success() = 0;

    virtual ~Response() = default;
};

struct UserResponse : Response {
    QString email;
    QString password;
    QString user_role;
    QString company_id;

    UserResponse(const QString& type, const QString& email_, const QString& password_, const QString& user_role_) \
        : Response(type), email(std::move(email_)), password(std::move(password_)),\
          user_role(std::move(user_role_)) {};

    void set_company_id(qint32 company_id_) {
        company_id = QString::number(company_id_);
    }

    bool is_success() override {
        return (!email.toStdString().empty() && !password.toStdString().empty() && !user_role.toStdString().empty());
    }

    QJsonDocument to_qjson_document() override {
        main_data["type"] = event_type;
        main_data["status"] = status;
        main_data["error_text"] = error_text;
        main_data["recipient"] = recipient;

        main_data["email"] = email;
        main_data["password"] = password;
        main_data["user_role"] = user_role;
        main_data["company_id"] = company_id;
        return QJsonDocument(main_data);
    }
};

}

#endif // RESPONSETEMPLATE_H
