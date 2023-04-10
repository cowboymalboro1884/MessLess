#ifndef DATABASE_PROJECT_HPP
#define DATABASE_PROJECT_HPP

#include "database.h"

namespace messless {
class Task{
public:
    std::string task_name;
    std::string deadline;
    std::string condition;
};
class DatabaseProject {
public:
    static unsigned int create_project(
        Database &db,
        PrivateUserInfo &user,
        const std::string &project_name,
        const std::string &biography
    );

    static void add_user_in_project(
        Database &db,
        PrivateUserInfo &user,
        unsigned int project_id,
        const std::string &user_role
    );

    static unsigned int get_project_id(
        Database &db,
        PrivateUserInfo &user,
        const std::string &project_name
    );

    static std::vector<std::string>
    get_projects(Database &db, PrivateUserInfo &user);

    static std::vector<User>
    get_project_user_list(Database &db, unsigned int project_id);

    static std::vector<Task>
    get_tasks(Database &db, unsigned int project_id);

    static unsigned int create_new_task(
        Database &db,
        unsigned int project_id,
        const std::string &task_name,
        const std::string &description,
        const std::string &deadline,  //"2013-07-21 00:00:00" год-месяц-день
                                      // часы:минуты:секунды
        const std::vector<User> &users
    );

    static void change_task_condition(Database &db, unsigned int task_id, const std::string& new_condition);

    static unsigned int get_task_id(Database &db, unsigned int project_id, const std::string& task_name);

    static void add_user_to_task(
        Database &db,
        unsigned int task_id,
        unsigned int user_id,
        unsigned int role
    );

    static bool is_project_exist(
        Database &db,
        PrivateUserInfo &user,
        const std::string &project_name
    );

    void delete_project(Database &db, unsigned int project_id);

    void delete_task(Database &db,unsigned int task_id);
};
}  // namespace messless
#endif
