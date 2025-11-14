#include "employee.h"
#include <fstream>
#include <sstream>
#include "library.h"
#include "customerorder.h"
#include "user.h"
#include "purchaseorder.h"
#include "product.h"
#include "warehouse.h"
#include <iomanip>
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
    cout<<"4.Xem danh sach san pham noi bat"<<endl;
    cout<<"5.Thong ke don hang trong ngay"<<endl;
    cout<<"6.Xem danh sach don hang ton kho"<<endl;
    cout<<"7.Xem danh sach san pham can nhap them"<<endl;
    cout<<"8.Dieu chinh gia ban san pham"<<endl;
    cout<<"9.Dang xuat"<<endl;
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
                string s;
                cout<<"Nhap Enter quay lai";getline(cin,s);
                current_Employee.employee_menu();
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
            string s;
            cout<<"Nhan Enter de quay lai";getline(cin,s);
            current_Employee.employee_menu();
            break;
        }
        case 3:{
            for (int i=0;i<Employee_List.getsize();i++)
                Employee_List[i].ShowInfo();
            string s;
            cout<<"Nhan Enter de quay lai";getline(cin,s);
            current_Employee.employee_menu();
            break;
        }
        case 4:{
            Product p;
            Vector<Product> list;
            p.sx(Product_List, list);
            
            string s; 

            cout << "\n=== SAN PHAM NOI BAT (TOP 5) ===\n";
            if (list.getsize() == 0) {
                cout << "Khong co san pham nao.\n";
                break;
            }

            cout << left
                << setw(50) << "Ten san pham"
                << setw(50) << "Loai"
                << setw(10) << "Gia"
                << setw(10) << "Da ban"
                << endl;
            cout << string(120, '-') << endl;

            int n=min(list.getsize(),5);
            for (int i = 0; i <n; i++) {
                list[i].showinfo();
            }
            cout<<"Nhan Enter de quay lai";getline(cin,s);
            current_Employee.employee_menu();
        }
        case 5:{
            string date,s;
            cout<<"Nhap ngay thang nam(dd/mm/yyyy)";getline(cin,date);
            Vector <PurchaseOrder> r1;
            Vector <CustomerOrder> r2;
            PurchaseOrder p1;CustomerOrder c1;
            int sum1=0,sum2=0;
            cout<<"Phieu nhap:"<<endl;
            p1.order_date(PurchaseOrder_List,r1,date);
            for (int i=0;i<r1.getsize();i++){
                r1[i].show();
                sum1+=r1[i].getsum();
            }
            cout<<"Tong tien trong ngay:"<<sum1<<endl;
            cout<<"Hoa don:"<<endl;
            c1.order_date(CustomerOrder_List,r2,date);
            for (int i=0;i<r2.getsize();i++){
                r2[i].show();
                sum2+=r2[i].getsum();
            }
            cout<<"Tong tien trong ngay"<<sum2<<endl;
            cout<<"Nhan Enter de quay lai";getline(cin,s);
            current_Employee.employee_menu();
            break;
        }
        case 6:{
            
        }
        case 7:{
            int id;
            Vector<Product> pr;
            cout<<"Nhap ma kho can xem thong tin:";cin>>id;cin.ignore();
            Warehouse w,tmp;
            Product p,t;
            w=tmp.Find_by_id(id,Warehouse_List);
            for (int i=0;i<w.Get_Inventory_size();i++){
                if (w.Get_Quantity(w.Get_Product_id(i))<15){
                    p=t.Find_byid(w.Get_Product_id(i),Product_List);
                    pr.push_back(p);
                }
            }
            t.Show(pr);
            break;
        }
        case 8:{
            Product p,t;
            string s;
            int pr;
            cout<<"Nhap id san pham muon dieu chinh gia:";getline(cin,s);
            cout<<"Nhap gia san pham:";cin>>pr;cin.ignore();
            p=t.Find_byid(s,Product_List);
            p.Set_price(pr);
            cout<<"Da thay doi gia thanh cong";
            cout<<"Nhan Enter de tro ve";getline(cin,s);
            current_Employee.employee_menu();
            break;
        }
        case 9:{
            main_menu();
            break;
        }
    }
}
