#ifndef DATABASE_CPP
#define DATABASE_CPP

#include"../include/database.hpp"
#include<vector>
#include<string>
namespace messless{
	Database::Database(const std::string& config_file){
		std::ifstream input(config_file);
		std::string connection_string;
		std::getline(input, connection_string);
    		connection(connection_string.c_str());
    		worker(connection);
	}
	DatabaseUser::login_user();
}
#endif
