#include <fstream>
#include <iostream>
#include<vector>
#include "../include/database.hpp"
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
    std::cout << messless::DatabaseCompany::create_user(
                     db, "amogus11@gmail.com", "zalupa", "Vladimir", "Krasnoe Solnyshko",
                     1, "employee"
                 )
                     .email
              << "User creating\n";*/
    /*std::cout << messless::DatabaseUser::login_user(
                     db, "amogus@gmail.com", "quwuqewq!!!"
                 )
                     .email
              << ' '
              << messless::DatabaseUser::login_user(
                     db, "amogus@gmail.com", "quwuqewq!!!"
                 )
                     .password
              << ' '
              << messless::DatabaseUser::login_user(
                     db, "amogus@gmail.com", "quwuqewq!!!"
                 )
                     .user_role
              << "User login\n";*/
    messless::PrivateUserInfo user_info1 =messless::DatabaseUser::login_user(db, "amogus@gmail.com", "quwuqewq!!!");
    //std::cout<< messless::DatabaseProject::create_project(db,user_info1,"my_project","")<<"Creating project\n";
    //std::cout<< messless::DatabaseProject::get_project_id(db,user_info1,"my_project")<<"Project id\n";
    unsigned int prID =messless::DatabaseProject::get_project_id(db,user_info1,"my_project");
    //messless::PrivateUserInfo user_info2 =messless::DatabaseUser::login_user(db,"amogus11@gmail.com","zalupa");
    //messless::DatabaseProject::add_user_in_project(db,user_info2,prID,"moderator");
    std::vector<messless::User> project1_users = messless::DatabaseProject::get_project_user_list(db,prID);
    for (auto &x:project1_users){
        std::cout<<x.name<<" "<<x.surname<<" "<<x.email<<" "<<x.user_role<<'\n';
    }
}
