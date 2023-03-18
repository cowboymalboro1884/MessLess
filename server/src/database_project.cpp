#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "../include/database.hpp"
namespace messless {
unsigned int DatabaseProject::create_project(
    Database &db,
    UserInfo &user,
    const std::string &project_name,
    const std::string &biography
) {
    std::unique_lock lock(db.database_mutex);
    pqxx::work worker(db.connection);
    worker.exec(
        "INSERT INTO projects (project_name,bio) VALUES('" +
        db.shield_string(project_name) + "','" + db.shield_string(biography) +
        "')"
    );
    unsigned int projects_id = worker.query_value<int>(
        "SELECT id FROM projects ORDER BY id DESC LIMIT 1;"
    );
    worker.commit();
    lock.unlock();
    add_user_in_project(db, user, projects_id, "admin");
    return projects_id;
}

unsigned int DatabaseProject::get_project_id(
    Database &db,
    UserInfo &user,
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
    }
    catch(...){
        return 0;
    }
}

void DatabaseProject::add_user_in_project(Database &db,
                                          UserInfo &user,
                                          unsigned int project_id,
                                          const std::string &user_role;) {
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
    try{
        std::vector<unsigned int> user_id_list;
        user_id_list = worker.query_value<std::vector<int>>("SELECT user_id from users_project_relationship WHERE project_id='"+db.shield_string(std::to_string(project_id))+"';");
        std::vector<User> user_list;
        for (auto user_id:user_id_list){
            User current_user;
            current_user.email=worker.query_value<std::string>("SELECT email FROM users WHERE id='"+db.shield_string(std::to_string(user_id))+"';");
            current_user.name=worker.query_value<std::string>("SELECT first_name FROM users WHERE id='"+db.shield_string(std::to_string(user_id))+"';";
            current_user.surname=worker.query_value<std::string>("SELECT second_name FROM users WHERE id='"+db.shield_string(std::to_string(user_id))+"';";
            unsigned user_role_id=worker.query_value<int>("SELECT project_role_id FROM users_project_relationship WHERE project_id='"+db.shield_string(std::to_string(project_id))+"' AND user_id='"+db.shield_string(std::to_string(user_id))+"';");
            current_user.user_role=worker.query_value<std::string>("SELECT role_description FROM project_roles WHERE id='"+db.shield_string(std::to_string(user_role_id))+"';");
            user_list.push_back(current_user);
        }
        return user_list;
    }
    catch(...)
    {
        return {};
    }
}
};

#endif