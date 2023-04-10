#include <fstream>
#include <iostream>
#include <pqxx/pqxx>
#include <string>

int main() {
    std::ifstream input("../../database.config");

    std::string connectionString;

    std::getline(input, connectionString);
    try {
        pqxx::connection connectionObject(connectionString.c_str());

        pqxx::work worker(connectionObject);
        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS users (
                        id serial  PRIMARY KEY,
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
                        );)sql");  // create users

        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS employee_roles(
                        id int PRIMARY KEY,
                        role_description character varying(32) NOT NULL
                        )WITH (
                        OIDS=FALSE
                        );)sql");

        /*worker.exec(R"sql(INSERT INTO employee_roles
                        (id,role_description)
                        VALUES (1,'admin'))sql");
        worker.exec(R"sql(INSERT INTO employee_roles
                        (id,role_description)
                        VALUES (2,'moderator'))sql");
        worker.exec(R"sql(INSERT INTO employee_roles
                        (id,role_description)
                        VALUES (3,'employee'))sql");*/
        // TODO general_chat_id with NOT NULL, because company have chat
        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS companies (
                        id serial PRIMARY KEY,
                        company_name character varying(32) NOT NULL,
                        bio character varying(256),
                        logo_link character varying(64),
                        general_chat_id bigint
                        ) WITH (
                        OIDS=FALSE
                        );)sql");  // create companies
        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS projects(
                        id serial PRIMARY KEY,
                        project_name character varying(32) NOT NULL,
                        company_id bigint NOT NULL,
                        chat_id bigint,
                        bio character varying(256)
                        ) WITH (
                        OIDS=FALSE
                        );)sql");  // create projects
        worker.exec(
            R"sql(CREATE TABLE IF NOT EXISTS users_projects_relationship (
                        user_id bigint NOT NULL,
                        project_id bigint NOT NULL,
                        project_role_id int NOT NULL
                        ) WITH (
                        OIDS=FALSE
                        );)sql"
        );  // create
        // user-projects
        // relationship
        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS messages (
                        id serial PRIMARY KEY,
                        chat_id bigint NOT NULL,
                        text_message character varying(1024),
                        file_link character varying(64),
                        sender_id bigint NOT NULL
                        ) WITH (
                          OIDS=FALSE
                         );)sql");  // create messages
        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS chats (
                        id serial PRIMARY KEY,
                        company_id bigint NOT NULL,
                        project_id bigint
                        ) WITH (
                        OIDS=FALSE
                        );)sql");  // create chats
        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS tasks(
                        id serial PRIMARY KEY,
                        task_name character varying(32) NOT NULL,
                        project_id bigint NOT NULL,
                        description character varying(256),
                        condition_id int NOT NULL,
                        deadline TIMESTAMP,
                        creation_time TIMESTAMP NOT NULL DEFAULT NOW()
                        ) WITH (
                        OIDS=FALSE
                        );)sql");  // create tasks
        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS condition (
                        id int PRIMARY KEY,
                        condition_description character varying(32) NOT NULL
                        ) WITH (
                        OIDS=FALSE
                        );)sql");  // create task  conditions
        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS users_tasks_relationship (
                        user_id bigint NOT NULL,
                        task_id bigint NOT NULL,
                        role int NOT NULL
                        ) WITH (
                        OIDS=FALSE
                       );)sql");   // create user-tasks
        // relationship
        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS roles (
                        id int NOT NULL,
                        role_description character varying(32) NOT NULL
                        ) WITH (
                        OIDS=FALSE
                        );)sql");  // create roles in tasks
        worker.exec(R"sql(CREATE TABLE IF NOT EXISTS project_roles(
                        id serial PRIMARY KEY,
                        role_description character varying(32) NOT NULL
                        )WITH (
                        OIDS=FALSE
                        );)sql");  // create project roles
        /*worker.exec(R"sql(INSERT INTO roles(id,role_description) VALUES(1,'admin');)sql");
        worker.exec(R"sql(INSERT INTO roles(id,role_description) VALUES(2,'moderator');)sql");
        worker.exec(R"sql(INSERT INTO roles(id,role_description) VALUES(3,'employee');)sql");*/
        worker.exec(R"sql(INSERT INTO condition(id,condition_description) VALUES(1,'to do');)sql");
        worker.exec(R"sql(INSERT INTO condition(id,condition_description) VALUES(2,'in process');)sql");
        worker.exec(R"sql(INSERT INTO condition(id,condition_description) VALUES(3,'done');)sql")
        worker.commit();
        std::cout << "Creating tables ended correctly" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;

    }
}
