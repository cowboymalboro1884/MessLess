#include <fstream>
#include <iostream>
#include "database.hpp"

int main() {
    std::ifstream input("../../../database.config");
    std::string private_salt, connection_string;
    std::getline(input, connection_string);
    std::getline(input, private_salt);
    messless::Database db(connection_string, private_salt);
    messless::DatabaseCompany::create_company(
        db, "ababa", "we are good company"
    );
    std::cout << "0" << std::endl;
    std::cout << messless::DatabaseCompany::create_user(
                     db, "amogus@gmail.com", "quwuqewq!!!", "Mikhail", "Ivanov",
                     1, "admin"
                 )
                     .email
              << "1\n";
    std::cout << messless::DatabaseUser::login_user(
                     db, "amogus@gmail.com", "quwuqewq!!!1"
                 )
                     .email
              << ' '
              << messless::DatabaseUser::login_user(
                     db, "amogus@gmail.com", "quwuqewq!!!1"
                 )
                     .password
              << ' '
              << messless::DatabaseUser::login_user(
                     db, "amogus@gmail.com", "quwuqewq!!!1"
                 )
                     .user_role
              << "2\n";
    std::cout << messless::DatabaseUser::login_user(
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
              << "3\n";
    std::cout << messless::DatabaseUser::login_user(
                     db, "amogus@gmail.com1", "quwuqewq!!!"
                 )
                     .email
              << ' '
              << messless::DatabaseUser::login_user(
                     db, "amogus@gmail.com1", "quwuqewq!!!"
                 )
                     .password
              << ' '
              << messless::DatabaseUser::login_user(
                     db, "amogus@gmail.com1", "quwuqewq!!!"
                 )
                     .user_role
              << "4\n";
}
