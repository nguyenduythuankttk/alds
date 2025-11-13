#include "employee.h"
#include <fstream>
#include <sstream>
#include "library.h"
#include "customerorder.h"
#include "user.h"
#include "purchaseorder.h"
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
int Employee::getEmployeeID() const{return this->employeeID;}
void Employee::employee_menu() const{
    menu:
    cout<<" ------------------------------ "<<endl;
    cout<<"|             Menu             |"<<endl;
    cout<<" ------------------------------ "<<endl;
    cout<<"1.Tra cuu don hang nguoi dung"<<endl;
    cout<<"2.Nhap phieu"<<endl;
    cout<<"3.Xem danh sach nhan vien"<<endl;
    cout<<"4.Thong ke don hang trong ngay"<<endl;
    cout<<"5.Xem danh sach don hang noi bat"<<endl;
    cout<<"6.Dang xuat"<<endl;
    int lc;
    cout<<"Moi lua chon:";cin>>lc;cin.ignore();
    switch (lc){
        case 1:{
            int s;
            Vector <CustomerOrder> result;
            CustomerOrder co;
            User u;
            User tmp;
            id:
            cout<<"Nhap id nguoi dung:";cin>>s;cin.ignore();
            if (u.find_by_id(s)) {
                u=tmp.id(s);
                co.order_by(u,CustomerOrder_List,result);
                for (int i=0;i<result.getsize();i++) result[i].show();
            }
            else {
                char c;
                cout<<"Chua ton tai nguoi dung.Thoat(Y/N)?";
                cin>>c; cin.ignore(); c=toupper(c);
                if (c=='Y') goto menu;
                else goto id;
            }
            break;
        }
        case 2:{
            PurchaseOrder pu;
            pu.create_PurchaseOrder(PurchaseOrder_List);
            break;
        }
        case 3:{
            for (int i=0;i<Employee_List.getsize();i++)
                Employee_List[i].ShowInfo();
            break;
        }
        case 4:{

        }
        case 5:{

        }
        case 6:{
            main_menu();
        }
    }
}