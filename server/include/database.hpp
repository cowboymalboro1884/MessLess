#ifndef DATABASE_HPP
#define DATABASE_HPP
#include "encrypting.hpp"
#include <boost/noncopyable.hpp>
#include <fstream>
#include <pqxx/pqxx>
#include <string>
#include <vector>
#include<iostream>

//TODO make without available SQL-injections

namespace messless {
class UserInfo{
public:
    std::string email;
    std::string password;
    std::string user_role;
};
class Database : private boost::noncopyable {
    pqxx::connection connection;
    messless::Encrypting crypt;
    void do_query_without_answer(const std::string& query);
    void do_queries_without_answer(std::vector< std::string> &queries);
    std::string shield_string(const std::string& unprotected_string);
public:
    explicit Database(const std::string &connection_string,const std::string &private_salt);
    friend class DatabaseGeneral;
    friend class DatabaseUser;
    friend class DatabaseCompany;
};

class DatabaseGeneral {
public:
};

class DatabaseUser {
public:
    static UserInfo login_user(
        Database &db,
        const std::string &email,
        const std::string &password
    );  // returns user id or zero if user doesn't exist
};

class DatabaseCompany {
public:
    static void create_company(
        Database &db,
        const std::string &company_name,
        const std::string &company_bio
    );  // returns company id
    static UserInfo create_user(
        Database &db,
        const std::string &email,
        const std::string &password,
        const std::string &name,
        const std::string &surname,
        unsigned int company_id,
        const std::string &user_role
    );  // return user id
};
}  // namespace messless
#endif
