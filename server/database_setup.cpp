#include <fstream>
#include <iostream>
#include <pqxx/pqxx>
#include <string>
int main() {
    std::ifstream input("database.config");

    std::string connectionString;

    std::getline(input, connectionString);
    try {
        pqxx::connection connectionObject(connectionString.c_str());

        pqxx::work worker(connectionObject);
        worker.exec(R"sql(DROP TABLE users)sql");

        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS users (
                        id bigint  PRIMARY KEY,
                        first_name character varying(32) NOT NULL,
                        second_name character varying(32) NOT NULL,
                        avatar_link character varying(64),
                        company_id bigint NOT NULL,
                        email character varying(32) NOT NULL UNIQUE,
                        password character varying(256) NOT NULL,
                        biography character varying(256),
                        salt character varying(128),
                        employee_role_id bigint NOT NULL
                        ) WITH (
                        OIDS=FALSE
                        );)sql"); // create users

        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS employee_roles(
                        id int PRIMARY KEY,
                        role_description character varying(32) NOT NULL
                        )WITH (
                        OIDS=FALSE
                        );)sql");

        worker.exec(R"sql(INSERT INTO employee_roles
                        (id,role_description)
                        (1,'admin'))sql");
        worker.exec(R"sql(INSERT INTO employee_roles
                        (id,role_description)
                        (2,'moderator'))sql");
        worker.exec(R"sql(INSERT INTO employee_roles
                        (id,role_description)
                        (3,'employee'))sql");

        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS companies (
                        id bigint PRIMARY KEY,
                        company_name character varying(32) NOT NULL,
                        bio character varying(256),
                        logo_link character varying(64),
                        general_chat_id bigint NOT NULL
                        ) WITH (
                        OIDS=FALSE
                        );)sql"); // create companies
        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS projects(
                        id bigint PRIMARY KEY,
                        company_id bigint NOT NULL,
                        chat_id bigint NOT NULL,
                        bio character varying(256),
                        desk_id bigint NOT NULL
                        ) WITH (
                        OIDS=FALSE
                        );)sql"); // create projects
        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS users_projects_relationship (
                        user_id bigint NOT NULL,
                        project_id bigint NOT NULL,
                        project_role_id int NOT NULL
                        ) WITH (
                        OIDS=FALSE
                        );)sql"); // create
        // user-projects
        // relationship

        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS messages (
                        id bigint PRIMARY KEY,
                        chat_id bigint NOT NULL,
                        text_message character varying(1024),
                        file_link character varying(64),
                        sender_id bigint NOT NULL
                        ) WITH (
                          OIDS=FALSE
                         );)sql");                          // create messages

        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS desk (
                        id bigint NOT NULL,
                        project_id bigint NOT NULL
                        ) WITH (
                        OIDS=FALSE
                        );)sql");         // create desk
        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS chats (
                        id bigint PRIMARY KEY,
                        company_id bigint NOT NULL,
                        project_id bigint NOT NULL
                        ) WITH (
                        OIDS=FALSE
                        );)sql"); // create chats
        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS tasks(
                        id bigint PRIMARY KEY,
                        desk_id bigint NOT NULL,
                        description character varying(256),
                        condition_id int NOT NULL,
                        deadline TIMESTAMP,
                        creation_time TIMESTAMP NOT NULL,
                        type character varying(32)
                        ) WITH (
                        OIDS=FALSE
                        );)sql"); // create tasks
        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS condition (
                        id int PRIMARY KEY,
                        condition_description character varying(32) NOT NULL
                        ) WITH (
                        OIDS=FALSE
                        );)sql"); // create task  conditions
        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS users_tasks_relationship (
                        user_id bigint NOT NULL,
                        task_id bigint NOT NULL,
                        role int NOT NULL
                        ) WITH (
                        OIDS=FALSE
                       );)sql"); // create user-tasks
        // relationship
        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS roles (
                        id character varying NOT NULL,
                        role_description character varying(32) NOT NULL
                        ) WITH (
                        OIDS=FALSE
                        );)sql"); // create roles in tasks
        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS project_roles(
                        id int PRIMARY KEY,
                        role_description character varying(32) NOT NULL
                        )WITH (
                        OIDS=FALSE
                        );)sql");                 // create project roles
        worker.commit();
        std::cout << "Creating tables ended correctly" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}







