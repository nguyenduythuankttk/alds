#include "person.h"
#include <iostream>
class Employee:public Person{
    private:
        int employeeID;
    public:
        Employee();
        Employee(const int&,const string&,const string&);
        ~Employee();
        void SetemployeeID(const int &);
        void ShowInfo() const;
};
Employee::Employee(){}
Employee::Employee(const int&ID,const string& username,const string& password):
    Person(username,password),employeeID(ID){}
Employee::~Employee(){}
void Employee::ShowInfo() const{
    cout<<"ID nguoi dung:"<<employeeID<<endl;
    cout<<"Ten tai khoan:"<<username<<endl;
    cout<<"Mat khau::"<<password<<endl;
}
void Employee::SetemployeeID(const int& ID){
    this->employeeID=ID;
}