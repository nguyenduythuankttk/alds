#pragma once
#include <string>
using namespace std;
class Person{
    protected:
        string username;
        string password;
    public:
        Person();
        Person(const string&,const string&);
        ~Person();
        string Getusername() const;
        string Getpassword() const;
        void Setusername(const string&);
        void Setpassword(const string&);
        
};
Person::Person(){
}
Person::Person(const string& username,const string& password):username(username),password(password){}
Person::~Person(){};
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