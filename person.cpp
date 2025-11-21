#include "person.h"
Person::Person(){}
Person::Person(const string& username,const string& password,const string& fullname,const string& phone,const string& email,const string& address)
    :username(username),password(password),address(address),fullname(fullname),phone(phone),email(email){}
Person::~Person(){}
string Person::Getpassword() const {
    return password;
}
string Person::Getusername() const{
    return username;
}
string Person::GetFullname() const{
    return fullname;
}
string Person::GetPhone() const{
    return phone;
}
string Person::GetEmail() const{
    return email;
}
string Person::GetAddress() const{
    return address;
}
void Person::Setusername(const string& username){
    this->username=username;
}
void Person::Setpassword(const string& password){
    this->password=password;
}
void Person::SetFullname(const string& fullname){
    this->fullname=fullname;
}
void Person::SetPhone(const string& phone){
    this->phone=phone;
}
void Person::SetEmail(const string& email){
    this->email=email;
}
void Person::SetAddress(const string& address){
    this->address=address;
}
