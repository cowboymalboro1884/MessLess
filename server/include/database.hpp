#ifndef DATABASE_HPP
#define DATABASE_HPP
#include<pqxx/pqxx>
#include<string>
#include<boost/noncopyable.hpp>

namespace messless{
class Database: private boost::noncopyable{
	pqxx::connection connection;
       	pqxx::work worker;
public:
    	Database(const std::string& config_file);
    	friend class DatabaseGeneral;
    	friend class DatabaseUser;
    	friend class DatabaseCompany;
}
class DatabaseGeneral{
public:
    
}

class DatabaseUser{
public:
   static  unsigned int login_user(Database &db,const std::string& email,const std::string& password)//returns user id or zero if user doesn't exist
   
}

class DatabaseCompany{
public:
    static unsigned int create_company(Database &db,const std::string& company_name, const std::string& company_bio);//returns company id
    static unsigned int create_user(Database &db, const std::string& email, const std::string& password, const std::string& name, const std::string& surname, unsigned int company_id, const std::string& user_role);//return user id 
}
}
#endif
