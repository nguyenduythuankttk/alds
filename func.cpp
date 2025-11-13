#include "library.h"
#include "warehouse.h"   
#include "product.h"      
#include "user.h"         
#include "employee.h"     
#include "purchaseorder.h"
#include "customerorder.h"
using namespace std;
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
    bool a=false;
    do{
        cout<<"Nhap ten dang nhap:";
        getline(cin,username);
        cout<<"Nhap mat khau:";
        getline(cin,password);
        for (int i=0;i<v.getsize();i++){
            if (v[i].Getpassword()==password && v[i].Getusername()==username){
                cur_User=v[i];
                a=true;
            }
        }
        count++;
    }while (count<3 && a==false);
    if (count>=3){
        char c;
        cout<<"Tai khoan chua ton tai.Tao tai khoan?(Y/N)";cin>>c;cin.ignore();
        c=toupper(c);
        if (c=='Y') sign_up(v);
        else main_menu();
        return;
    }
    cout<<"Da dang nhap thanh cong!\n";
}
void employee_sign_in(Employee &cur_Employee,const Vector<Employee>& v){
        string username,password;
    int count;
    count =0;
    bool a=false;
    do{
        cout<<"Nhap ten dang nhap:";
        getline(cin,username);
        cout<<"Nhap mat khau:";
        getline(cin,password);
        for (int i=0;i<v.getsize();i++){
            if (v[i].Getpassword()==password && v[i].Getusername()==username){
                cur_Employee=v[i];
                a=true;
            }
        }
        count++;
    }while (count<3 && a==false);
    if (a==false){ cout<<"Khong ton tai nhan vien nay"<<endl;
    main_menu();}
    else cur_Employee.employee_menu();
    return;
}
void main_menu(){
    cout<<" ------------------------------ "<<endl;
    cout<<"|        Menu dang nhap        |"<<endl;
    cout<<" ------------------------------ "<<endl;
    cout<<"1.Dang nhap"<<endl;
    cout<<"2.Dang ky"<<endl;
    cout<<"3.Dang nhap voi tu cach nhan vien"<<endl;
    cout<<"4.Thoat"<<endl;
    cout<<"Moi lua chon:";
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