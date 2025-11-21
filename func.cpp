#include "library.h"
#include "warehouse.h"   
#include "product.h"      
#include "user.h"         
#include "employee.h"     
#include "purchaseorder.h"
#include "customerorder.h"
#include <thread>
#include <chrono>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include <cctype>
using namespace std;
void choose_warehouse(Warehouse &w){
    if (Warehouse_List.getsize()==0){
        cout<<"[Thong bao] Chua co kho nao trong he thong.\n";
        return;
    }
    cout << "\n=============================================\n";
    cout << "|               CHON KHO GAN BAN              |\n";
    cout << "==============================================\n";
    cout << left
         << setw(5) << "STT"
         << setw(8) << "Ma"
         << setw(25) << "Ten kho"
         << "Dia chi\n";
    cout << string(70,'-') << "\n";
    for (int i=0;i<Warehouse_List.getsize();i++){
        cout << left
             << setw(5) << i+1
             << setw(8) << Warehouse_List[i].Get_ID()
             << setw(25) << Warehouse_List[i].Get_Name()
             << Warehouse_List[i].Get_Address() << "\n";
    }
    cout << string(70,'-') << "\n";
    kho:
    while (true){
        cout<<"=> Nhap STT kho (0 de quay lai): ";
        int stt;
        if (!(cin>>stt)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"Lua chon khong hop le. Vui long thu lai.\n";
            goto kho;
        }
        cin.ignore();
        if (stt==0) {
            clear_screen();
            main_menu();
        }
        if (stt<1 || stt>Warehouse_List.getsize()){
            cout<<"STT hop le. Vui long thu lai.\n";
            goto kho;
        }
        Warehouse tmp;
        w=tmp.Find_by_Address(Warehouse_List,Warehouse_List[stt-1].Get_Address());
        cout<<"Da chon kho: "<<w.Get_Name()<<" ("<<w.Get_Address()<<")\n";
        break;
    }
}
void clear_screen(){
    std::this_thread::sleep_for(std::chrono::seconds(2));
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void sign_up(Vector <User>&v){
    string name,password,confirm_password;
    User u;
    create_username:
    cout<<"Nhap ten dang nhap:";
    getline(cin,name);
    for (int i=0;i<v.getsize();i++){
        if (v[i].Getusername()==name){
            cout<<"Da co nguoi dung su dung ten nay.Vui long chon ten khac";
            goto create_username;
            break;
        }
    }
    create_password:
    cout<<"Nhap mat khau:";
    getline(cin,password);
    cout<<"Xac nhan mat khau:";
    getline(cin,confirm_password);
    if (password!=confirm_password) {
        cout<<"Nhap sai mat khau.Vui long tao lai mat khau";
        goto create_password;
    }
    string address;
    cout<<"Nhap dia chi:";getline(cin,address);
    u=User(v.getsize(),name,password,address);
    v.push_back(u);
    cout<<"Da tao tai khoan thanh cong. Tro ve menu chinh"<<endl;
    main_menu();
}
void user_sign_in(User &cur_User,Vector <User>&v){
    string username,password;
    int count;
    count =0;
    bool b=false;
    do{
        cout<<"Nhap ten dang nhap:";
        getline(cin,username);
        cout<<"Nhap mat khau:";
        getline(cin,password);
        for (int i=0;i<v.getsize();i++){
            if (v[i].Getpassword()==password && v[i].Getusername()==username){
                cur_User=v[i];
                b=true;
            }
        }
        count++;
    }while (count<3 && b==false);
    if (count>=3){
        char c;
        cout<<"Tai khoan chua ton tai.Tao tai khoan?(Y/N)";cin>>c;cin.ignore();
        c=toupper(c);
        if (c=='Y') sign_up(v);
        else main_menu();
        return;
    }
    cout<<"Da dang nhap thanh cong!\n";
    choose_warehouse(a);
}
void employee_sign_in(Employee &cur_Employee,const Vector<Employee>& v){
        string username,password;
    int count;
    count =0;
    bool b=false;
    do{
        cout<<"Nhap ten dang nhap:";
        getline(cin,username);
        cout<<"Nhap mat khau:";
        getline(cin,password);
        for (int i=0;i<v.getsize();i++){
            if (v[i].Getpassword()==password && v[i].Getusername()==username){
                cur_Employee=v[i];
                b=true;
            }
        }
        count++;
    }while (count<3 && b==false);
    if (b==false){ cout<<"Khong ton tai nhan vien nay"<<endl;
    main_menu();}
    else cur_Employee.employee_menu();
}
void main_menu(){
    clear_screen();
    cout << "\n========================================\n";
    cout << "|             MENU DANG NHAP           |\n";
    cout << "========================================\n";
    cout << "| 1 | Dang nhap nguoi dung             |\n";
    cout << "| 2 | Dang ky tai khoan                |\n";
    cout << "| 3 | Dang nhap voi tu cach nhan vien  |\n";
    cout << "| 4 | Thoat chuong trinh               |\n";
    cout << "----------------------------------------\n";
    cout << "Moi lua chon (1-4): ";
    int choice;cin>>choice;
    cin.ignore();
    switch (choice){
        case 1:{
            user_sign_in(current_User,User_List);
            current_User.user_menu();
            Warehouse tmp;
            string address=current_User.getAddress();
            a=tmp.Find_by_Address(Warehouse_List,address);
            a.ProductList(inWarehouse);
            break;
        }
        case 2:
            sign_up(User_List);
            break;
        case 3:
            employee_sign_in(current_Employee,Employee_List);
            break;
        case 4:{
            return;
            break;
        }
    }
    return;
}
string normalize(const string &s) { //chuẩn hoá chuỗi
    string result;
    stringstream ss(s);
    string word;
    while (ss >> word) { //xoá bỏ khoảng trắng
        if (!result.empty()) result += " ";
        result += word;
    }
    transform(result.begin(), result.end(), result.begin(),     // chuyển về lowercase
              [](unsigned char c){ return tolower(c); });

    return result;
}
bool timChuoi(const string &a, const string &b) {
    string A = normalize(a);
    string B = normalize(b);
    if (B.find(A) != string::npos) 
        return true;
    return false;
}
bool _date(const string& date) {
    if (date.size()!=10) return false; // kiểm tra đúng định dạng đầu vào
    if (date[2]!='/' || date[5]!='/') return false; //kiểm tra đúng định dạng đầu vào
    for (int i=0;i<10;i++){
        if (i==2 || i==5) continue;
        if (!isdigit(static_cast<unsigned char>(date[i]))) return false; // đưa hết toàn bộ chuỗi vào 1 chuỗi mới
    }
    int d = stoi(date.substr(0,2));
    int m = stoi(date.substr(3,2));
    int y = stoi(date.substr(6,4));
    if (y < 2023 || y > 2025) return false;
    if (m < 1 || m > 12) return false;
    int daysInMonth[] = {31, (y%4==0 && y%100!=0) || (y%400==0) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (d < 1 || d > daysInMonth[m-1]) return false;
    if (y == 2023 && (m < 1 || (m == 1 && d < 1))) return false;
    if (y == 2025 && (m > 12 || (m == 12 && d > 31))) return false;
    return true;
}
