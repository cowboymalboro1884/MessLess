#ifndef RESPONSETEMPLATE_H
#define RESPONSETEMPLATE_H

#include <QJsonDocument>
#include <QJsonObject>
#include <string>
#include <vector>

namespace templates::ResponseTemplate {

struct Response {
    QString event_type;
    QString status;
    QString recipient;
    QString error_text;
    QString message;
    QString company_id;

    QJsonObject main_data;

    Response(const QString &event_type_) : event_type(std::move(event_type_)){};

    void set_status(const QString &status_) {
        status = std::move(status_);
    }

    void set_error_text(const QString &error_text_) {
        error_text = std::move(error_text_);
    }

    void set_recipient(const QString &recipient_) {
        recipient = std::move(recipient_);
    }

    void set_message(const QString &message_) {
        message = std::move(message_);
    }

    void set_company_id(int company_id_) {
        company_id = QString::number(company_id_);
    }

    virtual QJsonDocument to_qjson_document() {
        main_data["type"] = event_type;
        main_data["status"] = status;
        main_data["error_text"] = error_text;
        main_data["recipient"] = recipient;
        main_data["message"] = message;
        main_data["company_id"] = company_id;

        return QJsonDocument(main_data);
    };

    virtual bool is_success() {
        return (status == "success");
    };

    virtual ~Response() = default;
};

struct InvalidJSONResposne : Response {
    static InvalidJSONResposne& get_instance() {
            static InvalidJSONResposne instance;
            return instance;
        }
private:
    InvalidJSONResposne() : Response("error") {
        status = "failed";
        error_text = "Invalid JSON";
    };
};

struct MissingRequestTypeResposne : Response {
    static MissingRequestTypeResposne& get_instance() {
            static MissingRequestTypeResposne instance;
            return instance;
        }
private:
    MissingRequestTypeResposne() : Response("error") {
        status = "failed";
        error_text = "Missing request type";
    };
};

struct UserResponse : Response {
    QString email;
    QString password;
    QString user_role;

    UserResponse(
        const QString &type,
        const QString &email_,
        const QString &password_,
        const QString &user_role_
    )
        : Response(type),
          email(std::move(email_)),
          password(std::move(password_)),
          user_role(std::move(user_role_)){};

    void set_company_id(int company_id_) {
        company_id = QString::number(company_id_);
    }

    bool is_success() override {
        return (
            !email.toStdString().empty() && !password.toStdString().empty() &&
            !user_role.toStdString().empty()
        );
    }

    QJsonDocument to_qjson_document() override {
        Response::to_qjson_document();

        main_data["email"] = email;
        main_data["password"] = password;
        main_data["user_role"] = user_role;
        return QJsonDocument(main_data);
    }
};

struct TaskResponse : Response {
    QString task_id;
    std::vector<std::string> emails_of_recipients;
    QString string_of_users_to_send;

    TaskResponse(const QString &type) : Response(type){};

    void set_task_id(int task_id_) {
        task_id = QString::number(task_id_);
    }

    void add_to_recipients(const std::string &user_email) {
        emails_of_recipients.push_back(user_email);
    }

    QJsonDocument to_qjson_document() override {
        Response::to_qjson_document();

        for (const auto &user_email : emails_of_recipients) {
            string_of_users_to_send += QString::fromStdString(user_email) + '|';
        }

        main_data["emails_of_recipients"] = string_of_users_to_send;
        main_data["task_id"] = task_id;

        return QJsonDocument(main_data);
    }
};

struct ProjectResponse : Response {
    QString project_id;
    QString project_name;
    QString project_bio;

    ProjectResponse(const QString &type_) : Response(type_){};

    void set_project_id(int project_id_) {
        project_id = QString::number(project_id_);
    }

    void set_project_name(const QString &project_name_) {
        project_name = std::move(project_name_);
    }

    void set_project_bio(const QString &project_bio_) {
        project_bio = std::move(project_bio_);
    }

    QJsonDocument to_qjson_document() override {
        Response::to_qjson_document();

        main_data["project_id"] = project_id;
        main_data["project_name"] = project_name;
        main_data["project_bio"] = project_bio;
        return QJsonDocument(main_data);
    }
};

struct ChatResponse : Response {
    QString name_of_sender;
    QString surname_of_sender;
    QString user_role;
    QString file_link;

    ChatResponse(const QString &type_) : Response(type_){};

    void set_name_of_sender(const QString &name_of_sender_) {
        name_of_sender = std::move(name_of_sender_);
    }

    void set_surname_of_sender(const QString &surname_of_sender_) {
        surname_of_sender = std::move(surname_of_sender_);
    }

    void set_user_role(const QString &user_role_) {
        user_role = std::move(user_role_);
    }

    void set_file_link(const QString &file_link_) {
        file_link = std::move(file_link_);
    }

    QJsonDocument to_qjson_document() override {
        Response::to_qjson_document();

        main_data["name_of_sender"] = name_of_sender;
        main_data["surname_of_sender"] = surname_of_sender;
        main_data["user_role"] = user_role;
        main_data["file_link"] = file_link;

        return QJsonDocument(main_data);
    }
};

}  // namespace templates::ResponseTemplate

#endif  // RESPONSETEMPLATE_H
