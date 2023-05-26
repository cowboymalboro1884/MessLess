#include <fstream>
#include <iostream>
#include <vector>
#include "../include/database.hpp"
#include "../include/database_chats.hpp"
#include "../include/database_project.hpp"

int main() {
    std::ifstream input("../../../database.config");
    std::string private_salt, connection_string;
    std::getline(input, connection_string);
    std::getline(input, private_salt);
    messless::Database db(connection_string, private_salt);
    messless::PrivateUserInfo user_info1 =
        messless::DatabaseUser::login_user(db, "ab", "ab");
    messless::PrivateUserInfo user_info2 =
        messless::DatabaseUser::login_user(db, "abtest", "abtest");

    unsigned int new_project = messless::DatabaseProject::create_project(
        db, user_info1, "new_project", "bio"
    );

    messless::DatabaseProject::add_user_in_project(
        db, user_info2.email, new_project, "employee"
    );

    unsigned int task_id = messless::DatabaseProject::create_new_task(
        db, new_project, "new task", "bio", "2013-07-21 00:00:00",
        {messless::DatabaseChats::from_private_user_info_to_user(
            db, user_info1
        )}
    );

    messless::DatabaseProject::add_user_to_task(
        db, task_id, user_info2.email, "employee"
    );

    for (auto x:messless::DatabaseProject::get_tasks(db,new_project)){
        std::cout<<x.task_name<<'\n';
    }
    std::cout<<'\n';
    messless::DatabaseProject::delete_task(db, task_id);

    for (auto x:messless::DatabaseProject::get_tasks(db,new_project)){
        std::cout<<x.task_name<<'\n';
    }
    messless::DatabaseProject::delete_user_from_project(
        db, user_info2.email, new_project
    );

    messless::DatabaseProject::add_user_in_project(
        db, user_info2.email, new_project, "employee"
    );

    messless::DatabaseProject::delete_project(db,new_project);
    // unsigned int new_task =
    // messless::DatabaseProject::create_new_task(db,new_project,"do
    // do","qweqw","2023-07-21 00:00:00",)
}
