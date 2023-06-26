#include "request_handler.cpp"

QJsonArray RequestHandler::get_raw_projects_and_tasks(
    PrivateUserInfo user  // DONE
) const noexcept {
    QJsonArray json_projects_with_tasks;

    std::vector<std::string> projects_to_update =
        DatabaseProject::get_projects(*database, user);

    for (const std::string &project_name : projects_to_update) {
        QJsonObject project_object;
        QJsonArray tasks;

        int project_id =
            DatabaseProject::get_project_id(*database, user, project_name);

        std::vector<Task> tasks_of_project =
            DatabaseProject::get_tasks(*database, project_id);

        for (const Task &task : tasks_of_project) {
            QJsonObject task_object;
            task_object["task_name"] = QString::fromStdString(task.task_name);
            task_object["task_condition"] =
                QString::fromStdString(task.condition);
            task_object["task_deadline"] =
                QString::fromStdString(task.deadline);
            tasks.append(task_object);
        }

        project_object["project_name"] = QString::fromStdString(project_name);
        project_object["tasks_array"] = tasks;
        json_projects_with_tasks.append(project_object);
    }

    return json_projects_with_tasks;
}

QJsonDocument RequestHandler::get_projects(const QJsonObject &request
) const {  // DONE
    qDebug() << "got for get project list";

    PrivateUserInfo sender = extract_user_info_from_qjson(request);

    GetProjectsWithUserResponse response;
    response.set_projects_of_company(get_raw_projects_and_tasks(sender));

    return response.to_qjson_document();
}

QJsonDocument RequestHandler::create_project(const QJsonObject &request
) const {  // DONE
    qDebug() << "----------------------------";
    qDebug() << "got for create project";

    PrivateUserInfo sender = extract_user_info_from_qjson(request);

    std::string project_name =
        request.value("project_name").toString().toStdString();
    std::string project_bio =
        request.value("project_bio").toString().toStdString();

    qDebug() << "name_of_project" << QString::fromStdString(project_name);
    qDebug() << "bio_of_project" << QString::fromStdString(project_bio);

    if (!DatabaseProject::is_project_exist(*database, sender, project_name)) {
        unsigned int company_id =
            DatabaseChats::get_company_id(*database, sender);
        unsigned int project_id = DatabaseProject::create_project(
            *database, sender, project_name, project_bio
        );

        qDebug() << "company id" << company_id;
        qDebug() << "project id " << project_id;

        return ProjectCreationIsSuccess(project_name).to_qjson_document();
    } else {
        return ProjectAlreadyExistError::get_instance().to_qjson_document();
    }
    qDebug() << "----------------------------";
}

QJsonDocument RequestHandler::add_or_delete_user_in_project(
    const QJsonObject &request
) const {  // DONE
    qDebug() << "got for add or delete user in project";

    PrivateUserInfo sender = extract_user_info_from_qjson(request);

    std::string project_name =
        request.value("project_name").toString().toStdString();

    std::string user_role_changed =
        request["user_role_changed"].toString().toStdString();

    std::string user_email_changed =
        request.value("user_email_changed").toString().toStdString();

    unsigned int project_id =
        DatabaseProject::get_project_id(*database, sender, project_name);

    if (request["type"] == "delete user from project") {
        DatabaseProject::delete_user_from_project(
            *database, user_email_changed, project_id
        );
    } else if (request["type"] == "add user in project") {
        qDebug() << "asd";
        DatabaseProject::add_user_in_project(
            *database, user_email_changed, project_id, user_role_changed
        );
    }

    ProjectUserDeletedOrAdded response(project_name);
    response.set_recipient(QString::fromStdString(user_email_changed));
    response.set_project_id(project_id);

    return response.to_qjson_document();
}

QJsonDocument RequestHandler::delete_project(const QJsonObject &request
) const {  // DONE i think
    PrivateUserInfo sender = extract_user_info_from_qjson(request);

    std::string project_name =
        request.value("project_name").toString().toStdString();
    std::string project_bio =
        request.value("project_bio").toString().toStdString();

    qDebug() << "name_of_project" << QString::fromStdString(project_name);
    qDebug() << "bio_of_project" << QString::fromStdString(project_bio);

    unsigned int project_id = DatabaseProject::create_project(
        *database, sender, project_name, project_bio
    );

    ProjectIsDeleted response(project_name);

    QJsonArray recipients;
    std::vector<User> user_list =
        DatabaseProject::get_project_user_list(*database, project_id);

    for (const auto &user : user_list) {
        QJsonObject email;
        email["email"] = QString::fromStdString(user.email);
        recipients.append(email);
    }
    response.set_recipients(recipients);

    DatabaseProject::delete_project(*database, project_id);

    return response.to_qjson_document();
}
