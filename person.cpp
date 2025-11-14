#include "person.h"
Person::Person(){}
Person::Person(const string& username,const string& password):username(username),password(password){}
Person::~Person(){}
string Person::Getpassword() const {
    return password;
}
string Person::Getusername() const{
    return username;
}
void Person::Setusername(const string& username){
    this->username=username;
}
void Person::Setpassword(const string& password){
    this->password=password;
}
