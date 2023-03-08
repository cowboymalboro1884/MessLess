#include"database.hpp"

int main(){
    messless::Database db("../../../database.config");
    messless::DatabaseCompany::create_company(db,"ababa","we are good company");
    messless::DatabaseCompany::create_user(db,"amogus@gmail.com","quwuqewq!!!","Mikhail","Ivanov",1,"admin");
}
