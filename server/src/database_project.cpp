#ifndef DATABASE_PROJECT_CPP
#define DATABASE_PROJECT_CPP
#include "../include/database_project.hpp"
#include <tuple>

namespace messless {
unsigned int DatabaseProject::create_project(
    Database &db,
    PrivateUserInfo &user,
    const std::string &project_name,
    const std::string &biography
) {
    try {
        pqxx::work worker(db.connection);
        unsigned int company_id = worker.query_value<int>(
            "SELECT company_id FROM users WHERE email='" +
            db.shield_string(user.email) + "';"
        );
        std::unique_lock lock(db.database_mutex);
        worker.exec(
            "INSERT INTO projects (company_id,project_name,bio) VALUES('" +
            db.shield_string(std::to_string(company_id)) + "','" +
            db.shield_string(project_name) + "','" +
            db.shield_string(biography) + "')"
        );
        unsigned int project_id = worker.query_value<int>(
            "SELECT id FROM projects ORDER BY id DESC LIMIT 1;"
        );
        worker.exec(
            "INSERT INTO chats (company_id,project_id) VALUES ('" +
            db.shield_string(std::to_string(company_id)) + "','" +
            db.shield_string(std::to_string(project_id)) + "')"
        );
        unsigned int chat_id = worker.query_value<int>(
            "SELECT id FROM chats ORDER BY id DESC LIMIT 1;"
        );
        worker.exec(
            "UPDATE projects SET chat_id ='" +
            db.shield_string(std::to_string(chat_id)) + "' WHERE id='" +
            db.shield_string(std::to_string(project_id)) + "';"
        );
        lock.unlock();
        worker.commit();
        add_user_in_project(db, user.email, project_id, "admin");
        return project_id;
    } catch (...) {
        return 0;
    }
}

unsigned int DatabaseProject::get_project_id(
    Database &db,
    PrivateUserInfo &user,
    const std::string &project_name
) {
    pqxx::work worker(db.connection);
    try {
        unsigned int company_id = worker.query_value<int>(
            "SELECT company_id FROM users "
            "WHERE email='" +
            db.shield_string(user.email) + "'"
        );
        unsigned int projects_id = worker.query_value<int>(
            "SELECT id FROM projects WHERE "
            "company_id='" +
            db.shield_string(std::to_string(company_id)) +
            "' AND project_name='" + db.shield_string(project_name) + "'"
        );
        return projects_id;
    } catch (...) {
        return 0;
    }
}

void DatabaseProject::add_user_in_project(
    Database &db,
    const std::string &email,
    unsigned int project_id,
    const std::string &user_role
) {
    try {
        pqxx::work worker(db.connection);
        unsigned int user_id = worker.query_value<int>(
            "SELECT id FROM users WHERE email='" + db.shield_string(email) +
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
            db.shield_string(std::to_string(user_id)) + "','" +
            db.shield_string(std::to_string(user_role_id)) + "')"
        );
        worker.commit();
    } catch (...) {
        return;
    }
}

std::vector<User>
DatabaseProject::get_project_user_list(Database &db, unsigned int project_id) {
    pqxx::work worker(db.connection);
    try {
        std::vector<unsigned int> user_id_list;
        std::vector<User> user_list;
        pqxx::result res = worker.exec(
            "SELECT user_id FROM users_projects_relationship WHERE "
            "project_id=" +
            db.shield_string(std::to_string(project_id)) + ";"
        );
        for (auto row : res) {
            unsigned int user_id = std::stoi(row[0].c_str());
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
            unsigned user_role_id = worker.query_value<int>(
                "SELECT project_role_id FROM users_projects_relationship WHERE "
                "project_id=" +
                db.shield_string(std::to_string(project_id)) + " AND user_id=" +
                db.shield_string(std::to_string(user_id)) + ";"
            );
            current_user.user_role = worker.query_value<std::string>(
                "SELECT role_description FROM project_roles WHERE id=" +
                db.shield_string(std::to_string(user_role_id)) + ";"
            );
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
        std::unique_lock lock(db.database_mutex);
        worker.exec(
            "INSERT INTO tasks "
            "(task_name,project_id,description,condition_id,deadline) VALUES "
            "('" +
            db.shield_string(task_name) + "','" +
            db.shield_string(std::to_string(project_id)) + "','" +
            db.shield_string(description) + "','" + db.shield_string("1") +
            "','" + db.shield_string(deadline) + "');"
        );
        unsigned int task_id = worker.query_value<int>(
            "SELECT id FROM tasks ORDER BY id DESC LIMIT 1;"
        );
        lock.unlock();
        for (auto &current_user : users) {
            unsigned int current_user_id = worker.query_value<int>(
                "SELECT id FROM users WHERE email='" +
                db.shield_string(current_user.email) + "';"
            );
            unsigned int role_id = worker.query_value<int>(
                "SELECT id FROM roles WHERE role_description='" +
                db.shield_string(current_user.user_role) + "';"
            );
            worker.exec(
                "INSERT INTO users_tasks_relationship (user_id,task_id,role) "
                "VALUES "
                "('" +
                db.shield_string(std::to_string(current_user_id)) + "','" +
                db.shield_string(std::to_string(task_id)) + "','" +
                db.shield_string(std::to_string(role_id)) + "');"
            );
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
    const std::string &email,
    const std::string &role_description
) {
    pqxx::work worker(db.connection);
    unsigned int user_id = worker.query_value<int>(
        "SELECT id FROM users WHERE email='" + db.shield_string(email) + "';"
    );
    unsigned int user_role_id = worker.query_value<int>(
        "SELECT id FROM roles WHERE role_description='" +
        db.shield_string(role_description) + "';"
    );
    worker.exec(
        "INSERT INTO users_tasks_relationship (user_id,task_id,role) VALUES "
        "('" +
        db.shield_string(std::to_string(user_id)) + "','" +
        db.shield_string(std::to_string(task_id)) + "','" +
        db.shield_string(std::to_string(user_role_id)) + "');"
    );
    worker.commit();
}

bool DatabaseProject::is_project_exist(
    Database &db,
    PrivateUserInfo &user,
    const std::string &project_name
) {
    if (get_project_id(db, user, project_name) == 0) {
        return false;
    }
    return true;
}

std::vector<std::string>
DatabaseProject::get_projects(Database &db, PrivateUserInfo &user) {
    std::vector<std::string> user_projects;
    pqxx::work worker(db.connection);
    unsigned int company_id = worker.query_value<int>(
        "SELECT company_id FROM users "
        "WHERE email='" +
        db.shield_string(user.email) + "'"
    );
    unsigned int user_id = worker.query_value<int>(
        "SELECT id FROM users WHERE email='" + db.shield_string(user.email) +
        "';"
    );
    pqxx::result res = worker.exec(
        "SELECT id, project_name FROM projects WHERE company_id=" +
        db.shield_string(std::to_string(company_id)) + ";"
    );
    for (auto row : res) {
        unsigned int project_id = std::stoi(row[0].c_str());
        std::string project_name = row[1].c_str();
        try {
            unsigned int role = worker.query_value<int>(
                "SELECT project_role_id FROM users_projects_relationship WHERE "
                "project_id=" +
                db.shield_string(std::to_string(project_id)) + " AND user_id=" +
                db.shield_string(std::to_string(user_id)) + " ;"
            );
            user_projects.push_back(project_name);
        } catch (...) {
            continue;
        }
    }
    worker.commit();
    return user_projects;
}

std::vector<Task>
DatabaseProject::get_tasks(Database &db, unsigned int project_id) {
    std::vector<Task> tasks;
    pqxx::work worker(db.connection);
    pqxx::result res = worker.exec(
        "SELECT id, task_name FROM tasks WHERE project_id=" +
        db.shield_string(std::to_string(project_id)) + ";"
    );
    for (auto row : res) {
        unsigned int id = std::stoi(row[0].c_str());
        std::string task_name = row[1].c_str();
        Task current_task{};
        current_task.task_name = task_name;
        current_task.deadline = worker.query_value<std::string>(
            "SELECT deadline FROM tasks WHERE id=" +
            db.shield_string(std::to_string(id)) + ";"
        );
        unsigned int condition_id = worker.query_value<int>(
            "SELECT condition_id FROM tasks WHERE id=" +
            db.shield_string(std::to_string(id)) + ";"
        );
        current_task.condition = worker.query_value<std::string>(
            "SELECT condition_description FROM condition WHERE id=" +
            db.shield_string(std::to_string(condition_id)) + ";"
        );
        tasks.push_back(current_task);
    }
    worker.commit();
    return tasks;
}

void DatabaseProject::change_task_condition(
    Database &db,
    unsigned int task_id,
    const std::string &new_condition
) {
    pqxx::work worker(db.connection);
    unsigned int new_condition_id = worker.query_value<int>(
        "SELECT id FROM condition WHERE condition_description='" +
        new_condition + "';"
    );
    worker.exec(
        "UPDATE tasks SET condition_id =" +
        db.shield_string(std::to_string(new_condition_id)) +
        " WHERE id=" + db.shield_string(std::to_string(task_id)) + " ;"
    );
    worker.commit();
}

unsigned int DatabaseProject::get_task_id(
    Database &db,
    unsigned int project_id,
    const std::string &task_name
) {
    try {
        pqxx::work worker(db.connection);
        unsigned int task_id = worker.query_value<int>(
            "SELECT id FROM tasks WHERE task_name='" +
            db.shield_string(task_name) + "' AND project_id=" +
            db.shield_string(std::to_string(project_id)) + ";"
        );
        worker.commit();
        return task_id;
    } catch (...) {
        return 0;
    }
}

void DatabaseProject::delete_project(Database &db, unsigned int project_id) {
    pqxx::work worker(db.connection);
    pqxx::result res = worker.exec(
        "SELECT id FROM tasks WHERE project_id=" +
        db.shield_string(std::to_string(project_id)) + ";"
    );
    for (auto row : res) {
        unsigned int id = std::stoi(row[0].c_str());
        worker.exec(
            "DELETE FROM users_tasks_relationship WHERE task_id=" +
            db.shield_string(std::to_string(id)) + ";"
        );
    }
    worker.exec(
        "DELETE FROM tasks WHERE project_id=" +
        db.shield_string(std::to_string(project_id)) + ";"
    );
    worker.exec(
        "DELETE FROM users_projects_relationship WHERE project_id=" +
        db.shield_string(std::to_string(project_id)) + ";"
    );
    worker.exec(
        "DELETE FROM projects WHERE id=" +
        db.shield_string(std::to_string(project_id)) + ";"
    );
    worker.commit();
}

void DatabaseProject::delete_task(Database &db, unsigned int task_id) {
    pqxx::work worker(db.connection);
    worker.exec(
        "DELETE FROM tasks WHERE id=" +
        db.shield_string(std::to_string(task_id)) + ";"
    );
    worker.exec(
        "DELETE FROM users_tasks_relationship WHERE task_id=" +
        db.shield_string(std::to_string(task_id)) + ";"
    );
    worker.commit();
}

void DatabaseProject::delete_user_from_project(
    Database &db,
    const std::string &email,
    unsigned int project_id
) {
    try {
        pqxx::work worker(db.connection);
        unsigned int user_id = worker.query_value<int>(
            "SELECT id FROM users WHERE email='" + db.shield_string(email) +
            "';"
        );
        pqxx::result res = worker.exec(
            "SELECT id FROM tasks WHERE project_id=" +
            db.shield_string(std::to_string(project_id)) + ";"
        );
        for (auto row : res) {
            unsigned int id = std::stoi(row[0].c_str());
            try {
                unsigned int count = worker.query_value<int>(
                    "SELECT COUNT(*) FROM users_tasks_relationship WHERE "
                    "task_id=" +
                    db.shield_string(std::to_string(id)) + ";"
                );
                worker.exec(
                    "DELETE FROM users_tasks_relationship WHERE task_id=" +
                    db.shield_string(std::to_string(id)) + "AND user_id=" +
                    db.shield_string(std::to_string(user_id)) + ";"
                );
                if (count == 1) {
                    worker.exec(
                        "DELETE FROM tasks WHERE id=" +
                        db.shield_string(std::to_string(id)) + ";"
                    );
                }
            } catch (...) {
                continue;
            }
        }
        worker.exec(
            "DELETE FROM users_projects_relationship WHERE user_id=" +
            db.shield_string(std::to_string(user_id)) + " AND project_id=" +
            db.shield_string(std::to_string(project_id)) + ";"
        );
        worker.commit();
    } catch (...) {
        return;
    }
}

void DatabaseProject::delete_user_from_task(
    Database &db,
    unsigned int task_id,
    const std::string &email
) {
    pqxx::work worker(db.connection);
    unsigned int user_id = worker.query_value<int>(
        "SELECT id FROM users WHERE email='" + db.shield_string(email) + "';"
    );
    unsigned int count = worker.query_value<int>(
        "SELECT COUNT(*) FROM users_tasks_relationship WHERE "
        "task_id=" +
        db.shield_string(std::to_string(task_id)) + ";"
    );
    worker.exec(
        "DELETE FROM users_tasks_relationship WHERE task_id=" +
        db.shield_string(std::to_string(task_id)) +
        "AND user_id=" + db.shield_string(std::to_string(user_id)) + ";"
    );
    if (count == 1) {
        worker.exec(
            "DELETE FROM tasks WHERE id=" +
            db.shield_string(std::to_string(task_id)) + ";"
        );
    }
}

}  // namespace messless

#endif
