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
    messless::DatabaseProject::delete_project(db,messless::DatabaseProject::get_project_id(db,user_info1,"new_project"));
    unsigned int new_project = messless::DatabaseProject::create_project(
        db, user_info1, "new_project", "bio"
    );

    messless::DatabaseProject::add_user_in_project(
        db, user_info2.email, new_project, "employee"
    );
    auto t = messless::DatabaseChats::from_private_user_info_to_user(
        db, user_info1
    );
    t.user_role = "employee";
    std::cout<<t.surname<<' '<<t.name<<' '<<t.email<<' '<<t.user_role<<'\n';
    unsigned int task_id = messless::DatabaseProject::create_new_task(
        db, new_project, "new task", "bio", "2013-07-21 00:00:00",
        {t}
    );

    messless::DatabaseProject::add_user_to_task(
        db, task_id, user_info2.email, "employee"
    );
    auto y = messless::DatabaseProject::get_tasks(db,new_project);
    for (auto x:y){
        std::cout<<x.task_name<<'\n';
    }
    std::cout<<'\n';
    messless::DatabaseProject::delete_task(db, task_id);

    for (auto x:messless::DatabaseProject::get_tasks(db,new_project)){
        std::cout<<x.task_name<<'\n';
    }
    messless::DatabaseProject::delete_project(db,messless::DatabaseProject::get_project_id(db,user_info1,"new_project"));
    //messless::DatabaseProject::delete_project(db,new_project);
    // unsigned int new_task =
    // messless::DatabaseProject::create_new_task(db,new_project,"do
    // do","qweqw","2023-07-21 00:00:00",)
}
