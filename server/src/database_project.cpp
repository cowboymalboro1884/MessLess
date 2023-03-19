#ifndef DATABASE_PROJECT_CPP
#define DATABASE_PROJECT_CPP

#include "../include/database_project.hpp"

namespace messless {
unsigned int DatabaseProject::create_project(
    Database &db,
    PrivateUserInfo &user,
    const std::string &project_name,
    const std::string &biography
) {
    pqxx::work worker(db.connection);
    unsigned int company_id = worker.query_value<int>(
        "SELECT company_id FROM users WHERE email='" +
        db.shield_string(user.email) + "';"
    );
    std::unique_lock lock(db.database_mutex);
    worker.exec(
        "INSERT INTO projects (company_id,project_name,bio) VALUES('" +
        db.shield_string(std::to_string(company_id)) + "','" +
        db.shield_string(project_name) + "','" + db.shield_string(biography) +
        "')"
    );
    unsigned int project_id = worker.query_value<int>(
        "SELECT id FROM projects ORDER BY id DESC LIMIT 1;"
    );
    worker.exec(
        "INSERT INTO desk (project_id) VALUES ('" +
        db.shield_string(std::to_string(project_id)) + "')"
    );
    worker.exec(
        "INSERT INTO desk (project_id) VALUES ('" +
        db.shield_string(std::to_string(project_id)) + "')"
    );
    worker.exec(
        "INSERT INTO chats (company_id,project_id) VALUES ('" +
        db.shield_string(std::to_string(company_id)) + "','" +
        db.shield_string(std::to_string(project_id)) + "')"
    );
    unsigned int desk_id =
        worker.query_value<int>("SELECT id FROM desk ORDER BY id DESC LIMIT 1;"
        );
    ;
    unsigned int chat_id =
        worker.query_value<int>("SELECT id FROM chats ORDER BY id DESC LIMIT 1;"
        );
    worker.exec(
        "UPDATE projects SET (desk_id,chat_id) =('" +
        db.shield_string(std::to_string(desk_id)) + "','" +
        db.shield_string(std::to_string(chat_id)) "') WHERE id='" +
        db.shield_string(std::to_string(project_id)) + "';"
    );
    lock.unlock();
    worker.commit();
    add_user_in_project(db, user, project_id, "admin");
    return project_id;
}

unsigned int DatabaseProject::get_project_id(
    Database &db,
    PrivateUserInfo &user,
    const std::string &project_name
) {
    pqxx::work worker(db.connection);
    try {
        unsigned int company_id = worker.query_value<int>("SELECT company_id FROM users "
            "WHERE email='"+db.shield_string(user.email)+"'";
        unsigned int projects_id =
            worker.query_value<int>("SELECT id FROM projects WHERE "
                                        "company_id='"+db.shield_string(std::to_string(company_id))+"' AND project_name='"+db.shield_string(project_name)+"'"
            );
        return projects_id;
    } catch (...) {
        return 0;
    }
}

void DatabaseProject::add_user_in_project(
    Database &db,
    PrivateUserInfo &user,
    unsigned int project_id,
    const std::string &user_role
) {
    pqxx::work worker(db.connection);
    unsigned int user_id = worker.query_value<int>(
        "SELECT id FROM users WHERE email='" + db.shield_string(user.email) +
        "';"
    );
    unsigned int user_role_id = worker.query_value<int>(
        "SELECT id FROM project_roles WHERE role_description='" +
        db.shield_string(user_role) + "';"
    );
    worker.exec(
        "INSERT INTO users_projects_relationship "
        "(project_id,user_id,project_role_id) VALUES('" +
        db.shield_string(std::to_string(project_id)) + "','" +
        db.shield_string(std::to_string(user_role_id)) + "')"
    );
    worker.commit();
}

std::vector<User>
DatabaseProject::get_project_user_list(Database &db, unsigned int project_id) {
    pqxx::work worker(db.connection);
    try {
        std::vector<unsigned int> user_id_list;
        user_id_list = worker.query_value<std::vector<int>>(
            "SELECT user_id from users_project_relationship WHERE "
            "project_id='" +
            db.shield_string(std::to_string(project_id)) + "';"
        );
        std::vector<User> user_list;
        for (auto user_id : user_id_list) {
            User current_user;
            current_user.email = worker.query_value<std::string>(
                "SELECT email FROM users WHERE id='" +
                db.shield_string(std::to_string(user_id)) + "';"
            );
            current_user.name=worker.query_value<std::string>("SELECT first_name FROM users WHERE id='"+db.shield_string(std::to_string(user_id))+"';";
            current_user.surname=worker.query_value<std::string>("SELECT second_name FROM users WHERE id='"+db.shield_string(std::to_string(user_id))+"';";
            unsigned user_role_id=worker.query_value<int>("SELECT project_role_id FROM users_project_relationship WHERE project_id='"+db.shield_string(std::to_string(project_id))+"' AND user_id='"+db.shield_string(std::to_string(user_id))+"';");
            current_user.user_role=worker.query_value<std::string>("SELECT role_description FROM project_roles WHERE id='"+db.shield_string(std::to_string(user_role_id))+"';");
            user_list.push_back(current_user);
        }
        return user_list;
    } catch (...) {
        return {};
    }
}

unsigned int DatabaseProject::create_new_task(
    Database &db,
    unsigned int project_id,
    const std::string &task_name,
    const std::string &description,
    const std::string &deadline,
    const std::vector<User> &users
) {
    try {
        pqxx::work worker(db.connection);
        unsigned int desk_id = worker.query<int>(
            "SELECT id FROM desk WHERE project_id='" +
            db.shield_string(std::to_string(project_id)) + "';"
        );
        std::unique_lock lock(db.database_mutex);
        worker.exec(
            "INSERT INTO tasks "
            "(task_name,desk_id,description,condition_id,deadline,creation_"
            "time) VALUES ('" +
            db.shield_string(task_name) + "','" +
            db.shield_string(std::to_string(desk_id)) + "','" +
            db.shield_string(description) + "','" + db.shield_string("0") +
            "','" + db.shield_string(deadline) + "', now());"
        );
        unsigned int task_id = worker.query_value<int>(
            "SELECT id FROM tasks ORDER BY id DESC LIMIT 1;"
        );
        lock.unlock();
        for (auto &current_user : users) {
            unsigned int current_user_id = worker.query<int>(
                "SELECT id FROM users WHERE email='" +
                db.shield_string(current_user.email) + "';"
            );
            unsigned int role_id = worker.query<int>(
                "SELECT id FROM roles WHERE role_description='" +
                db.shield_string(current_user.user_role) + "';"
            );
            add_user_to_task(db, task_id, current_user_id, role_id);
        }
        worker.commit();
        return task_id;
    } catch (...) {
        return 0;
    }
}

void DatabaseProject::add_user_to_task(
    Database &db,
    unsigned int task_id,
    unsigned int user_id,
    unsigned int role
) {
    pqxx::work worker(db.connection);
    worker.exec(
        "INSERT INTO users_tasks_relationship (user_id,task_id,role) VALUES "
        "('" +
        db.shield_string(std::to_string(user_id)) + "','" +
        db.shield_string(std::to_string(task_id)) + "','" +
        db.shield_string(std::to_string(role)) + "');"
    );
    worker.commit();
}
};  // namespace messless

#endif