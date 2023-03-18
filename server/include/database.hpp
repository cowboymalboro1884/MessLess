#ifndef DATABASE_HPP
#define DATABASE_HPP
#include <boost/noncopyable.hpp>
#include <exception>
#include <fstream>
#include <iostream>
#include <mutex>
#include <pqxx/pqxx>
#include <string>
#include <thread>
#include <vector>
#include "encrypting.hpp"

namespace messless {
class PrivateUserInfo {
public:
    std::string email;
    std::string password;
    std::string user_role;
};

class User{
public:
    std::string name;
    std::string surname;
    std::string email;
    std::string user_role;
};

class Database : private boost::noncopyable {
    std::mutex database_mutex;
    pqxx::connection connection;
    messless::Encrypting crypt;
    void do_query_without_answer(const std::string &query);
    void do_queries_without_answer(std::vector<std::string> &queries);
    std::string shield_string(const std::string &unprotected_string);

public:
    explicit Database(
        const std::string &connection_string,
        const std::string &private_salt
    );
    friend class DatabaseGeneral;
    friend class DatabaseUser;
    friend class DatabaseCompany;
    friend class DatabaseProject;
};

class DatabaseGeneral {
public:
};

class DatabaseUser {
public:
    static PrivateUserInfo login_user(
        Database &db,
        const std::string &email,
        const std::string &password
    );  // returns user id or zero if user doesn't exist
};

class DatabaseCompany {
public:
    static unsigned int create_company(
        Database &db,
        const std::string &company_name,
        const std::string &company_bio
    );  // returns company id
    static PrivateUserInfo create_user(
        Database &db,
        const std::string &email,
        const std::string &password,
        const std::string &name,
        const std::string &surname,
        unsigned int company_id,
        const std::string &user_role
    );  // return user id
};

class DatabaseProject {
    static unsigned int create_project(
        Database &db,
        PrivateUserInfo &user,
        const std::string& project_name,
        const std::string& biography
    );
    static void add_user_in_project(
        Database &db,
        PrivateUserInfo &user,
        unsigned int project_id,
        const std::string& user_role
        );
    static unsigned int get_project_id(
        Database &db,
        PrivateUserInfo &user,
        const std::string& project_name
        );
    static std::vector<User> get_project_user_list(
        Database &db,
        unsigned int project_id
        );

};
}  // namespace messless
#endif
