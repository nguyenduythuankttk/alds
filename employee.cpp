#include "employee.h"
#include <fstream>
#include <sstream>
Employee::Employee(){}
Employee::Employee(const int&ID,const string& username,const string& password):
    Person(username,password),employeeID(ID){}
Employee::~Employee(){}
void Employee::ShowInfo() const{
    cout<<"ID nguoi dung:"<<employeeID<<endl;
    cout<<"Ten tai khoan:"<<username<<endl;
    cout<<"Mat khau::"<<password<<endl;
}
void Employee::readfile(Vector<Employee>& v){
    string s;
    int i;
    Employee e;
    ifstream filename("employee.txt");
    while (getline(filename,s)){
        if (s=="") continue;
        i=0;
        stringstream sub(s);
        while (getline(sub,s,',')){
            if (i==0) e.employeeID=stoi(s);
            else if(i==1) e.username=s;
            else e.password=s;
            i++;
        }
        v.push_back(e);
    }
}
void Employee::savefile(const Vector<Employee> &v) const{
    ofstream file("employee.txt");
    for (int i=0;i<v.getsize();i++){
        file<<v[i].employeeID<<","<<v[i].username<<","<<v[i].password<<"\n";
    }
}
void Employee::setEmployeeID(const int& ID) {
    this->employeeID=ID;
}