#include "employee.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "library.h"
#include "customerorder.h"
#include "user.h"
#include "purchaseorder.h"
#include "product.h"
#include "warehouse.h"
#include "chitietphieunhap.h"
#include <iomanip>
Employee::Employee(){}
Employee::Employee(const int&ID,const string& username,const string& password,const string& fullname,const string& phone,const string& email,const string& address):
    Person(username,password,fullname,phone,email,address),employeeID(ID){}
Employee::~Employee(){}
void Employee::ShowInfo() const{
    cout<<"ID nguoi dung:"<<employeeID<<endl;
    cout<<"Ten tai khoan:"<<username<<endl;
    cout<<"Mat khau:"<<password<<endl;
    cout<<"Ho ten:"<<fullname<<endl;
    cout<<"SDT:"<<phone<<endl;
    cout<<"Email:"<<email<<endl;
    cout<<"Dia chi:"<<address<<endl;
}
void Employee::readfile(Vector<Employee>& v){
    ifstream filename("employee.txt");
    string line;
    while (getline(filename,line)){
        if (line=="") continue;
        stringstream sub(line);
        string token;
        Employee e;
        int i=0;
        while (getline(sub,token,',')){
            switch(i){
                case 0: e.employeeID=stoi(token); break;
                case 1: e.username=token; break;
                case 2: e.password=token; break;
                case 3: e.fullname=token; break;
                case 4: e.phone=token; break;
                case 5: e.email=token; break;
                case 6: e.address=token; break;
            }
            i++;
        }
        v.push_back(e);
    }
}
void Employee::savefile(const Vector<Employee> &v) const{
    ofstream file("employee.txt");
    for (int i=0;i<v.getsize();i++){
        file<<v[i].employeeID<<","<<v[i].username<<","<<v[i].password<<","<<v[i].fullname<<","<<v[i].phone<<","<<v[i].email<<","<<v[i].address<<"\n";
    }
}
void Employee::setEmployeeID(const int& ID) {
    this->employeeID=ID;
}
int Employee::getEmployeeID() const{return this->employeeID;}
void Employee::employee_menu() const{
    menu:
    clear_screen();
    cout << "\n====================================================\n";
    cout << "|                 MENU NHAN VIEN                   |\n";
    cout << "====================================================\n";
    cout << "| 1 | Tra cuu don hang nguoi dung                  |\n";
    cout << "| 2 | Tao phieu nhap                               |\n";
    cout << "| 3 | Xem danh sach nhan vien                      |\n";
    cout << "| 4 | San pham noi bat                             |\n";
    cout << "| 5 | Thong ke don nhap trong ngay                 |\n";
    cout << "| 6 | Thong ke don ban ra trong ngay               |\n";
    cout << "| 7 | Danh sach don hang ton kho                   |\n";
    cout << "| 8 | San pham can nhap them                       |\n";
    cout << "| 9 | Dieu chinh gia ban san pham                  |\n";
    cout << "| 10| Xem danh sach nguoi dung                     |\n";
    cout << "| 11| Dang xuat                                    |\n";
    cout << "----------------------------------------------------\n";
    int lc;
    cout<<"=> Moi lua chon (1-10): ";cin>>lc;cin.ignore();
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
                co.order_by(CustomerOrder_List,result,u.GetID());
                if (result.getsize()==0){
                    cout<<"Nguoi dung chua co don hang nao.\n";
                } else {
                    cout<<"\n=== HOA DON CUA NGUOI DUNG "<<u.GetID()<<" ===\n";
                    cout<<left
                        <<setw(6)<<"ID"
                        <<setw(15)<<"Ngay"
                        <<setw(15)<<"Kho"
                        <<setw(15)<<"Tong tien"
                        <<endl;
                    cout<<string(51,'-')<<endl;
                    for (int i=0;i<result.getsize();i++){
                    Warehouse wh = a;
                    for (int j=0;j<Warehouse_List.getsize();j++)
                        if (Warehouse_List[j].Get_ID()==result[i].GetWarehouseID()) wh=Warehouse_List[j];
                    cout<<left
                        <<setw(6)<<result[i].getID()
                        <<setw(15)<<result[i].GetDate()
                        <<setw(15)<<wh.Get_ID()
                            <<setw(15)<<result[i].getsum()
                            <<endl;
                    }
                    while (true){
                        cout<<"Nhap ID hoa don de xem chi tiet (Enter de quay lai): ";
                        string input;
                        getline(cin,input);
                        if (input=="") break;
                        try{
                            int id=stoi(input);
                            bool found=false;
                            for (int i=0;i<result.getsize();i++){
                                if (result[i].getID()==id){
                                    result[i].show();
                                    found=true;
                                    break;
                                }
                            }
                            if (!found) cout<<"Khong tim thay ID hoa don.\n";
                        }catch(const invalid_argument&){
                            cout<<"Ma khong hop le.\n";
                        }
                    }
                }
                string pause;
                cout<<"Nhap Enter quay lai";getline(cin,pause);
                goto menu;
            }
            else {
                char c;
                cout<<"Chua ton tai nguoi dung. Thoat? (Y/N): ";
                cin>>c; cin.ignore(); c=toupper(c);
                if (c=='Y') goto menu;
                else goto id;
            }

            break;
        }
        case 2:{
            PurchaseOrder pu;
            pu.create_PurchaseOrder(PurchaseOrder_List);
            cout<<"Nhan Enter de quay lai";
            {
                string tmp;
                getline(cin,tmp);
            }
            goto menu;
        }
        case 3:{
            cout<<"\n=== DANH SACH NHAN VIEN ===\n";
            if (User_List.getsize()==0){
                cout<<"Khong co nhan vien nao.\n";
            } else {
                cout<<left
                    <<setw(6)<<"ID"
                    <<setw(20)<<"Tai khoan"
                    <<setw(20)<<"Ho ten"
                    <<setw(15)<<"SDT"
                    <<setw(25)<<"Email"
                    <<setw(25)<<"Dia chi"
                    <<endl;
                cout<<string(111,'-')<<endl;
                for (int i=0;i<Employee_List.getsize();i++){
                    cout<<left
                        <<setw(6)<<Employee_List[i].getEmployeeID()
                        <<setw(20)<<Employee_List[i].Getusername()
                        <<setw(20)<<Employee_List[i].GetFullname()
                        <<setw(15)<<Employee_List[i].GetPhone()
                        <<setw(25)<<Employee_List[i].GetEmail()
                        <<setw(25)<<Employee_List[i].GetAddress()
                        <<endl;
                }
            }
            cout<<"Nhan Enter de quay lai";
            {
                string tmp;
                getline(cin,tmp);
            }
            goto menu;
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
            goto menu;
        }
        case 5:{
            string date;
            do{
                cout<<"Nhap ngay thang nam(dd/mm/yyyy):";
                getline(cin,date);
                if (!_date(date)) cout<<"[Thong bao] Ngay khong hop le. Vui long nhap lai.\n";
            }while(!_date(date));
            Vector <PurchaseOrder> r1;
            PurchaseOrder p1;
            int sum1=0;
            cout<<"\n=== DON NHAP TRONG NGAY ===\n";
            p1.order_date(PurchaseOrder_List,r1,date);
            if (r1.getsize()==0) {
                cout<<"Khong co phieu nhap nao trong ngay.\n";
            } else {
                cout<<left
                    <<setw(6)<<"ID"
                    <<setw(15)<<"Ngay"
                    <<setw(12)<<"Nhan vien"
                    <<setw(10)<<"Kho"
                    <<setw(15)<<"Tong tien"
                    <<endl;
                cout<<string(58,'-')<<endl;
                for (int i=0;i<r1.getsize();i++){
                    cout<<left
                        <<setw(6)<<r1[i].GetID()
                        <<setw(15)<<r1[i].GetDate()
                        <<setw(12)<<r1[i].GetEmployeeID()
                        <<setw(10)<<r1[i].GetWarehouseID()
                        <<setw(15)<<r1[i].getsum()
                        <<endl;
                    sum1+=r1[i].getsum();
                }
            }
            cout<<"Tong chi phi nhap trong ngay: "<<sum1<<endl;
            while (true){
                cout<<"Nhap ma phieu nhap de xem chi tiet (Enter de quay lai): ";
                string input;
                getline(cin,input);
                if (input=="") break;
                bool handled=false;
                try{
                    int id=stoi(input);
                    for (int i=0;i<r1.getsize();i++){
                        if (r1[i].GetID()==id){
                            ChitietPhieunhap::show(hoadon_List,id);
                            handled=true;
                            break;
                        }
                    }
                    if (!handled){
                        cout<<"Khong tim thay ma trong danh sach ngay "<<date<<".\n";
                    }
                }catch(const invalid_argument&){
                    cout<<"Ma khong hop le.\n";
                }
            }
            cout<<"Nhan Enter de quay lai";
            {
                string tmp;
                getline(cin,tmp);
            }
            goto menu;
        }
        case 6:{
            string date;
            do{
                cout<<"Nhap ngay thang nam(dd/mm/yyyy):";
                getline(cin,date);
                if (!_date(date)) cout<<"[Thong bao] Ngay khong hop le. Vui long nhap lai.\n";
            }while(!_date(date));
            Vector <CustomerOrder> r2;
            CustomerOrder c1;
            int sum2=0;
            cout<<"\n=== HOA DON BAN TRONG NGAY ===\n";
            c1.order_date(CustomerOrder_List,r2,date);
            if (r2.getsize()==0) {
                cout<<"Khong co hoa don nao trong ngay.\n";
            } else {
                cout<<left
                    <<setw(6)<<"ID"
                    <<setw(10)<<"ID ND"
                    <<setw(10)<<"Kho"
                    <<setw(15)<<"Tong tien"
                    <<endl;
                cout<<string(41,'-')<<endl;
                for (int i=0;i<r2.getsize();i++){
                    cout<<left
                        <<setw(6)<<r2[i].getID()
                        <<setw(10)<<r2[i].GetCustomerID()
                        <<setw(10)<<r2[i].GetWarehouseID()
                        <<setw(15)<<r2[i].getsum()
                        <<endl;
                    sum2+=r2[i].getsum();
                }
            }
            cout<<"Tong doanh thu trong ngay: "<<sum2<<endl;
            while (true){
                cout<<"Nhap ma hoa don de xem chi tiet (Enter de quay lai): ";
                string input;
                getline(cin,input);
                if (input=="") break;
                bool handled=false;
                try{
                    int id=stoi(input);
                    for (int i=0;i<r2.getsize();i++){
                        if (r2[i].getID()==id){
                            r2[i].show();
                            handled=true;
                            break;
                        }
                    }
                    if (!handled){
                        cout<<"Khong tim thay hoa don trong danh sach ngay "<<date<<".\n";
                    }
                }catch(const invalid_argument&){
                    cout<<"Ma khong hop le.\n";
                }
            }
            cout<<"Nhan Enter de quay lai";
            {
                string tmp;
                getline(cin,tmp);
            }
            goto menu;
        }
        case 7:{
            string date;
            do{
                cout<<"Nhap ngay thang nam(dd/mm/yyyy):";
                getline(cin,date);
                if (!_date(date)) cout<<"[Thong bao] Ngay khong hop le. Vui long nhap lai.\n";
            }while(!_date(date));
            cout<<"\n=== SAN PHAM TON KHO (>6 THANG) ===\n";
            cout<<left
                <<setw(12)<<"ID"
                <<setw(30)<<"Ten"
                <<setw(20)<<"Loai"
                <<setw(12)<<"Gia"
                <<endl;
            cout<<string(74,'-')<<endl;
            int count=0;
            for (int i=0;i<Product_List.getsize();i++){
                if (Product_List[i].Is_Inventory_Product(date)){
                    cout<<left
                        <<setw(12)<<Product_List[i].Get_ID()
                        <<setw(30)<<Product_List[i].Get_Name()
                        <<setw(20)<<Product_List[i].Get_Cat()
                        <<setw(12)<<Product_List[i].Get_price()
                        <<endl;
                    count++;
                }
            }
            if (count==0) cout<<"Khong co san pham nao bi ton kho qua 6 thang.\n";
            cout<<"Nhan Enter de quay lai";
            {
                string tmp;
                getline(cin,tmp);
            }
            clear_screen();
            goto menu;
        }
        case 8:{
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
            cout<<"Nhan Enter de quay lai";
            {
                string tmp;
                getline(cin,tmp);
            }
            clear_screen();
            goto menu;
            break;
        }
        case 9:{
            Product p,t;
            string s;
            int pr;
            cout<<"Nhap id san pham muon dieu chinh gia:";getline(cin,s);
            cout<<"Nhap gia san pham:";cin>>pr;cin.ignore();
            p=t.Find_byid(s,Product_List);
            p.Set_price(pr);
            cout<<"Da thay doi gia thanh cong"<<endl;
            cout<<"Nhan Enter de tro ve"<<endl;
            {
                string tmp;
                getline(cin,tmp);
            }
            clear_screen();
            goto menu;
        }
        case 11:{
            clear_screen();
            main_menu();
            break;
        }
        case 10:{
            cout<<"\n=== DANH SACH NGUOI DUNG ===\n";
            if (User_List.getsize()==0){
                cout<<"Khong co nguoi dung nao.\n";
            } else {
                cout<<left
                    <<setw(6)<<"ID"
                    <<setw(20)<<"Tai khoan"
                    <<setw(20)<<"Ho ten"
                    <<setw(15)<<"SDT"
                    <<setw(25)<<"Email"
                    <<setw(25)<<"Dia chi"
                    <<endl;
                cout<<string(111,'-')<<endl;
                for (int i=0;i<User_List.getsize();i++){
                    cout<<left
                        <<setw(6)<<User_List[i].GetID()
                        <<setw(20)<<User_List[i].Getusername()
                        <<setw(20)<<User_List[i].GetFullname()
                        <<setw(15)<<User_List[i].GetPhone()
                        <<setw(25)<<User_List[i].GetEmail()
                        <<setw(25)<<User_List[i].GetAddress()
                        <<endl;
                }
            }
            cout<<"Nhan Enter de tro ve"<<endl;
            {
                string tmp;
                getline(cin,tmp);
            }
            clear_screen();
            goto menu;
            break;
        }
    }
}
