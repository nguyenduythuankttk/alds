#pragma once
#include <string>
using namespace std;
class Person{
    protected:
        string username;
        string password;
        string address;
    public:
        Person();
        Person(const string&,const string&);
        ~Person();
        string Getusername() const;
        string Getpassword() const;
        void Setusername(const string&);
        void Setpassword(const string&);
        
        
};

