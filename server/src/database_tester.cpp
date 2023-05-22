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
    /*std::cout << messless::DatabaseCompany::create_company(
                     db, "ababa", "we are good company"
                 )
              << "Company creating\n";
    std::cout << messless::DatabaseCompany::create_user(
                     db, "amogus@gmail.com", "quwuqewq!!!", "Mikhail", "Ivanov",
                     1, "admin"
                 )
                     .email
              << "User creating\n";
    */
    messless::PrivateUserInfo user_info1 = messless::DatabaseUser::login_user(
        db, "amogus@gmail.com", "quwuqewq!!!"
    ); /*
     std::cout<<
     messless::DatabaseProject::create_project(db,user_info1,"my_project","")<<"Creating
     \ project\n"; std::cout<<
     messless::DatabaseProject::get_project_id(db,user_info1,"my_project")<<"Project
     \ id\n";*/
    unsigned int prID =
        messless::DatabaseProject::get_project_id(db, user_info1, "my_project");
    messless::PrivateUserInfo user_info2 =
        messless::DatabaseUser::login_user(db, "amogus11@gmail.com", "zalupa");
    // messless::DatabaseProject::add_user_in_project(db,user_info2,prID,"moderator");
    /*std::vector<messless::User> project1_users =
        messless::DatabaseProject::get_project_user_list(db, prID);
    for (auto &x : project1_users) {
        std::cout << x.name << " " << x.surname << " " << x.email << " "
                  << x.user_role << '\n';
    }
    std::vector<std::string> projects_for_one_user =
        messless::DatabaseProject::get_projects(db, user_info1);
    for (auto &x : projects_for_one_user) {
        std::cout << x << '\n';
    }
    std::cout << "\n\n\n";
    messless::DatabaseProject::create_new_task(
        db, prID, "MY TASK", "MY DESCRIPTION", "2024-07-21 00:00:00",
        {{"Michail", "Ivanov", "amogus@gmail.com", "moderator"}}
    );
    std::vector<messless::Task> tasks =
        messless::DatabaseProject::get_tasks(db, prID);
    for (auto &x : tasks) {
        std::cout << x.task_name << " " << x.condition << " " << x.deadline
                  << '\n';
    }*/
    /*unsigned int chat_id_user_info1_company_chat =
    messless::DatabaseChats::get_chat_id(db,messless::DatabaseChats::get_company_id(db,user_info1),0);
    std::cout<<messless::DatabaseChats::get_company_id(db,user_info1)<<'\n';
    messless::DatabaseChats::send_message(db,chat_id_user_info1_company_chat,user_info1,"my
    message","");
    messless::DatabaseChats::send_message(db,chat_id_user_info1_company_chat,user_info1,"wow
    message","");
    messless::DatabaseChats::send_message(db,chat_id_user_info1_company_chat,user_info1,"my
    message","");
    messless::DatabaseChats::send_message(db,chat_id_user_info1_company_chat,user_info1,"my","");
    std::vector<messless::Message> m =
    messless::DatabaseChats::get_all_messages(db,chat_id_user_info1_company_chat);
    for (auto &x: m){
        std::cout<<x.sender.name<<' '<<x.sender.surname<<'
    '<<x.text_message<<'\n';
    }*/
    auto x = messless::DatabaseCompany::get_company_user_list(db, user_info1);
    for (auto y : x) {
        std::cout << y.name << ' ' << y.surname << ' ' << y.email << ' '
                  << y.user_role << '\n';
    }
    // unsigned int new_project =
    // messless::DatabaseProject::create_project(db,user_info1,"new_project","bio");
    // messless::DatabaseProject::add_user_in_project(db,user_info2.email,new_project,"employee");
    // unsigned int new_task =
    // messless::DatabaseProject::create_new_task(db,new_project,"do
    // do","qweqw","2023-07-21 00:00:00",)
}
