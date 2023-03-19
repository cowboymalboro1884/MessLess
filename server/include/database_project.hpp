#ifndef DATABASE_PROJECT_HPP
#define DATABASE_PROJECT_HPP

#include "database.hpp"

namespace messless {
class DatabaseProject {
    static unsigned int create_project(
        Database &db,
        PrivateUserInfo &user,
        const std::string &project_name,
        const std::string &biography
    );
    static void add_user_in_project(
        Database &db,
        PrivateUserInfo &user,
        unsigned int project_id,
        const std::string &user_role
    );
    static unsigned int get_project_id(
        Database &db,
        PrivateUserInfo &user,
        const std::string &project_name
    );
    static std::vector<User>
    get_project_user_list(Database &db, unsigned int project_id);
};
}  // namespace messless
#endif