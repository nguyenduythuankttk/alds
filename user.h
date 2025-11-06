#include "person.h"
#include <iostream>
using namespace std;
class User:public Person{
    private: 
        int userID;
    public:
        User();
        User(const int&,const string&,const string&);
        ~User();
        void SetuserID(const int&);
        void ShowInfo() const;

};
User::User(){}
User::User(const int&ID,const string& username,const string& password):
    Person(username,password),userID(ID){}
User::~User(){}
void User::ShowInfo() const{
    cout<<"ID nguoi dung:"<<userID<<endl;
    cout<<"Ten tai khoan:"<<username<<endl;
    cout<<"Mat khau::"<<password<<endl;
}
void User::SetuserID(const int& ID){
    this->userID=ID;
}