#pragma once
#include "person.h"
#include <iostream>
#include "vector.h"
class Employee:public Person{
    private:
        int employeeID;
    public:
        Employee();
        Employee(const int&,const string&,const string&);
        ~Employee();
        void setEmployeeID(const int&);
        void readfile(Vector<Employee>&);
        void savefile(const Vector<Employee>&) const;
        void ShowInfo() const;
};
