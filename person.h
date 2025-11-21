#pragma once
#include <string>
using namespace std;
class Person{
    protected:
        string username;
        string password;
        string address;
        string fullname;
        string phone;
        string email;
    public:
        Person();
        Person(const string& username,const string& password,const string& fullname="",const string& phone="",const string& email="",const string& address="");
        ~Person();
        string Getusername() const;
        string Getpassword() const;
        string GetFullname() const;
        string GetPhone() const;
        string GetEmail() const;
        string GetAddress() const;
        void Setusername(const string&);
        void Setpassword(const string&);
        void SetFullname(const string&);
        void SetPhone(const string&);
        void SetEmail(const string&);
        void SetAddress(const string&);
        
        
};
