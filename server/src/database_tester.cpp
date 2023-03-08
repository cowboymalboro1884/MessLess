#include"database.hpp"
#include<fstream>
#include<iostream>

int main(){
	
	std::ifstream input("../../../database.config");
    std::string private_salt,connection_string;
    std::getline(input,connection_string);
    std::getline(input,private_salt);
    messless::Database db(connection_string,private_salt);
    messless::DatabaseCompany::create_company(db,"ababa","we are good company");
    std::cout<<"1"<<std::endl;
    //messless::DatabaseCompany::create_user(db,"amogus@gmail.com","quwuqewq!!!","Mikhail","Ivanov",1,"admin");
    std::cout<<messless::DatabaseUser::login_user(db,"amogus@gmail.com","quwuqewq!!!").email<<' '<<messless::DatabaseUser::login_user(db,"amogus@gmail.com","quwuqewq!!!").password<<' '<<messless::DatabaseUser::login_user(db,"amogus@gmail.com","quwuqewq!!!").user_role;
}
