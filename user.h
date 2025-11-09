#include "person.h"
#include "global.cpp"
#pragma once
#include <iostream>
using namespace std;
class User:public Person{
    private: 
        int userID;
    public:
        User();
        User(const int&,const string&,const string&);
        User(const User&);
        ~User();
        void SetuserID(const int&);
        void ShowInfo() const;
        void readfile(Vector<User> &);
        void savefile(const Vector<User> &) const;
        int GetID() const;
        void user_menu();

};
