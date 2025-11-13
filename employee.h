#pragma once
#include "person.h"
#include "vector.h"

class Employee:public Person{
    private:
        int employeeID;
    public:
        Employee();
        Employee(const int&,const string&,const string&);
        ~Employee();
        void setEmployeeID(const int&);
        int getEmployeeID() const;
        void readfile(Vector<Employee>&);
        void savefile(const Vector<Employee>&) const;
        void ShowInfo() const;
        void employee_menu() const;
};
