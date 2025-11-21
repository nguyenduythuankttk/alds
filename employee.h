#pragma once
#include "person.h"
#include "vector.h"

class Employee:public Person{
    private:
        int employeeID;
    public:
        Employee();
        Employee(const int& id,const string& username,const string& password,const string& fullname="",const string& phone="",const string& email="",const string& address="");
        ~Employee();
        void setEmployeeID(const int&);
        int getEmployeeID() const;
        void readfile(Vector<Employee>&);
        void savefile(const Vector<Employee>&) const;
        void ShowInfo() const;
        void employee_menu() const;
        string Getusername() const {return username;}
        string Getpassword() const {return password;}
        string GetFullname() const {return fullname;}
        string GetPhone() const {return phone;}
        string GetEmail() const {return email;}
        string GetAddress() const {return address;}

};
