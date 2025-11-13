#pragma once
#include "person.h"
#include "vector.h"
using namespace std;
class User:public Person{
    private: 
        int userID;
        string address;
    public:
        User();
        User(const int&,const string&,const string&,const string&);
        User(const User&);
        ~User();
        void SetuserID(const int&);
        string getAddress() const;
        void ShowInfo() const;
        void readfile(Vector<User> &);
        void savefile(const Vector<User> &) const;
        int GetID() const;
        void user_menu() const;
        bool find_by_id(const int&) const;
        User& id(const int&) const;
};
