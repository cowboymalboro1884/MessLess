#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "../include/database.hpp"

namespace messless {
Database::Database(const std::string &config_file) {
    std::ifstream input(config_file);
    std::string connection_string;
    std::getline(input, connection_string);
    connection(connection_string.c_str());
    worker(connection);
}

void Database::do_query_without_answer(const std::string &query) {
    try {
        worker.exec(query);
        worker.commit();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Database::do_queries_without_answer(std::vector<const std::string> &queries
) {
    try {
        for (auto &current_query : queries) {
            worker.exec(current_query);
        }
        worker.commit();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

unsigned int DatabaseUser::login_user(
    Database &db,
    const std::string &email,
    const std::string &password
) {
    // TODO
}

unsigned int DatabaseCompany::create_company(
    Database &db,
    const std::string &company_name,
    const std::string &company_bio
) {
    db.do_query_without_answer(
        "INSERT INTO companies (company_name,bio)('" + company_name + "','" +
        company_bio + "')"
    );
    // TODO return id, which is last in table users
}

unsigned int DatabaseCompany::create_user(
    Database &db,
    const std::string &email,
    const std::string &password,
    const std::string &name,
    const std::string &surname,
    unsigned int company_id,
    const std::string &user_role
) {
    db.do_query_without_answer(
        "INSERT INTO users "
        "(first_name,second_name,company_id,email,password)('" +
        name + "','" + surname + "','" + std::to_string(company_id) + "','" +
        email + "','" + password + "')"
    );
    // TODO return id, which is last in table users
}
}  // namespace messless
#endif
