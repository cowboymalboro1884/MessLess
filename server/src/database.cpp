#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "../include/database.hpp"

//TODO make without available SQL-injections
namespace messless {
Database::Database(const std::string &config_file) {
    std::ifstream input(config_file);
    std::string connection_string;
    std::getline(input, connection_string);
    connection(connection_string.c_str());
    worker(connection);
    std::string salt;
    std::getline(input,salt);
    crypt = std::move(Encrypting(salt));
    input.close();
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

std::string Database::shield_string(const std::string & unprotected_string) {
    return connection.esc(unprotected_string);
}

UserInfo DatabaseUser::login_user(
    Database &db,
    const std::string &email,
    const std::string &password
) {
    pqxx::result id = db.worker.exec(
        "SELECT id FROM users WHERE email='" + db.shield_string(email) + "' AND password='" +
        db.shield_string(password) + "';"
        );
    if (id.empty()){
        return {"",""};
    }
    return {email, password};
}

void DatabaseCompany::create_company(
    Database &db,
    const std::string &company_name,
    const std::string &company_bio
) {
    //TODO make without available SQL-injections
    db.do_query_without_answer(
        "INSERT INTO companies (company_name,bio)('" + db.shield_string(company_name) + "','" +
        db.shield_string(company_bio) + "')"
    );
}

UserInfo DatabaseCompany::create_user(
    Database &db,
    const std::string &email,
    const std::string &password,
    const std::string &name,
    const std::string &surname,
    unsigned int company_id,
    const std::string &user_role
) {
    //TODO make without available SQL-injections
    //TODO make in database column "salt" in "users"
    std::string new_salt = db.crypt.get_random_string();
    db.do_query_without_answer(
        "INSERT INTO users "
        "(first_name,second_name,company_id,email,password)('" +
        db.shield_string(name) + "','" + db.shield_string(surname) + "','" + db.shield_string(std::to_string(company_id)) + "','" +
        db.shield_string(email) + "','" + db.shield_string(db.crypt.get_password_hash(password,new_salt)) + "')"
    );
    return {email, password};
}
}  // namespace messless
#endif
