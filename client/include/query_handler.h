#ifndef QUERY_HANDLER_H
#define QUERY_HANDLER_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QString>

struct QuerySender : public QObject {
    Q_OBJECT
public:
public slots:

    void check_credentials(const QString &email, const QString &password);

    void register_company_and_user(
        const QString &email,
        const QString &password,

        const QString &name,
        const QString &surname,

        const QString &company_name,
        const QString &company_bio
    );

    void add_user_to_company(
        const QString &sender_email,
        const QString &sender_password,
        const QString &sender_user_role,

        const QString &email_to_add,
        const QString &password_to_add,
        const QString &user_role_to_add,

        const QString &name_to_add,
        const QString &surname_to_add
    );

    void get_tasks_of_projects(
        const QString &sender_email,
        const QString &sender_password,
        const QString &sender_user_role,

        const QString &project_name
    );

    void get_projects_of_company(
        const QString &sender_email,
        const QString &sender_password,
        const QString &sender_user_role
    );

    void create_project(
        const QString &sender_email,
        const QString &sender_password,
        const QString &sender_user_role,

        const QString &project_name,
        const QString &project_bio
    );

    void add_user_to_project(
        const QString &sender_email,
        const QString &sender_password,
        const QString &sender_user_role,

        const QString &email_added,
        const QString &user_role_added,
        const QString &project_name
    );

    void delete_user_to_project(
        const QString &sender_email,
        const QString &sender_password,
        const QString &sender_user_role,

        const QString &email_deleted,
        const QString &project_name
    );

    void delete_project(
        const QString &sender_email,
        const QString &sender_password,
        const QString &sender_user_role,

        const QString &project_name
    );
    void create_task(
        const QString &sender_email,
        const QString &sender_password,
        const QString &sender_user_role,

        const QString &task_name,
        const QString &description,
        const QString &deadline,
        const QString &project_name
    );

    void delete_task(
        const QString &sender_email,
        const QString &sender_password,
        const QString &sender_user_role,

        const QString &task_name,
        const QString &project_name
    );

    void change_task_condition(
        const QString &sender_email,
        const QString &sender_password,
        const QString &sender_user_role,

        const QString &task_name,
        const QString &project_name,
        const QString &new_condition
    );

    void send_message_to_company(
        const QString &sender_email,
        const QString &sender_password,
        const QString &sender_user_role,

        const QString &message
    );

    void send_message_to_project(
        const QString &sender_email,
        const QString &sender_password,
        const QString &sender_user_role,

        const QString &message,
        const QString &project_name
    );

signals:
    void ready_to_write_data_to_socket(const QByteArray &data);
};

#endif  // QUERY_HANDLER_H
