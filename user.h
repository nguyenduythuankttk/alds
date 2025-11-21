#pragma once
#include "person.h"
#include "vector.h"
using namespace std;
class User:public Person{
    private: 
        int userID;
    public:
        User();
        User(const int& id,const string& username,const string& password,const string& fullname="",const string& phone="",const string& email="",const string& address="");
        User(const User&);
        ~User();
        void SetuserID(const int&);
        string getAddress() const;
        string getFullname() const;
        string getPhone() const;
        string getEmail() const;
        void ShowInfo() const;
        void readfile(Vector<User> &);
        void savefile(const Vector<User> &) const;
        int GetID() const;
        void user_menu() const;
        bool find_by_id(const int&) const;
        User& id(const int&) const;
};
