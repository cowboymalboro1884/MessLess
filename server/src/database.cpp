#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "../include/database.hpp"

namespace messless {
Database::Database(
    const std::string &connection_string,
    const std::string &private_salt
)
    : connection(connection_string.c_str()), crypt(private_salt) {
}

void Database::do_query_without_answer(const std::string &query) {
    pqxx::work worker(connection);
    worker.exec(query);
    worker.commit();
}

void Database::do_queries_without_answer(std::vector<std::string> &queries) {
    try {
        pqxx::work worker(connection);
        for (auto &current_query : queries) {
            worker.exec(current_query);
        }
        worker.commit();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

std::string Database::shield_string(const std::string &unprotected_string) {
    return connection.esc(unprotected_string);
}

PrivateUserInfo DatabaseUser::login_user(
    Database &db,
    const std::string &email,
    const std::string &password
) {
    static std::string personal_salt;
    pqxx::work worker(db.connection);
    try {
        personal_salt = worker.query_value<std::string>(
            "SELECT salt FROM users WHERE email='" + db.shield_string(email) +
            "';"
        );
    } catch (std::exception &) {
        return {"", "", ""};
    }
    static std::string password_hash;
    password_hash = db.crypt.get_password_hash(password, personal_salt);
    int employee_role_id;
    try {
        employee_role_id = worker.query_value<int>(
            "SELECT employee_role_id FROM users WHERE email='" +
            db.shield_string(email) + "' AND password='" +
            db.shield_string(password_hash) + "';"
        );
        if (employee_role_id == 1) {
            return {email, password_hash, "admin"};
        }
        if (employee_role_id == 2) {
            return {email, password_hash, "moderator"};
        }
        if (employee_role_id == 3) {
            return {email, password_hash, "employee"};
        }
    } catch (std::exception &) {
        return {"", "", ""};
    }
    return {"", "", ""};
}

unsigned int DatabaseCompany::create_company(
    Database &db,
    const std::string &company_name,
    const std::string &company_bio
) {
    std::unique_lock lock(db.database_mutex);
    pqxx::work worker(db.connection);
    worker.exec(
        "INSERT INTO companies (company_name,bio) VALUES('" +
        db.shield_string(company_name) + "','" + db.shield_string(company_bio) +
        "')"
    );
    int company_id = worker.query_value<int>(
        "SELECT id FROM companies ORDER BY id DESC LIMIT 1;"
    );
    worker.exec("INSERT INTO chats (company_id,project_id) VALUES('"+db.shield_string(std::to_string(company_id))+"','"+'0'+"');");
    int chat_id = worker.query_value<int>(
        "SELECT id FROM chats ORDER BY id DESC LIMIT 1;"
    );
    worker.exec(
        "UPDATE companies SET general_chat_id =" +
        db.shield_string(std::to_string(chat_id)) + " WHERE id=" + db.shield_string(std::to_string(company_id)) +
        " ;"
    );
    worker.commit();
    return company_id;
}

PrivateUserInfo DatabaseCompany::create_user(
    Database &db,
    const std::string &email,
    const std::string &password,
    const std::string &name,
    const std::string &surname,
    unsigned int company_id,
    const std::string &user_role
) {
    int employee_user_role_id = 3;
    if (user_role == "admin") {
        employee_user_role_id = 1;
    }
    if (user_role == "moderator") {
        employee_user_role_id = 2;
    }
    if (user_role == "employee") {
        employee_user_role_id = 3;
    }
    static std::string new_salt;
    static std::string password_hash;
    new_salt = messless::Encrypting::get_random_string();
    password_hash = db.crypt.get_password_hash(password, new_salt);
    try {
        db.do_query_without_answer(
            "INSERT INTO users "
            "(first_name,second_name,company_id,email,password,salt,employee_"
            "role_id) VALUES('" +
            db.shield_string(name) + "','" + db.shield_string(surname) + "','" +
            db.shield_string(std::to_string(company_id)) + "','" +
            db.shield_string(email) + "','" + db.shield_string(password_hash) +
            "','" + db.shield_string(new_salt) + "','" +
            db.shield_string(std::to_string(employee_user_role_id)) + "');"
        );
    } catch (...) {
        return {"", "", ""};
    }
    return {email, password_hash, user_role};
}

}  // namespace messless
#endif
