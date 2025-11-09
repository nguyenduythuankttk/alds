#pragma once
#include "global.cpp"
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
    u=User(v.getsize(),name,password);
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
    }while (count<3 && a=false);
    if (count>=3){
        char c;
        cout<<"Tai khoan chua ton tai.Tao tai khoan?(Y/N)";cin>>c;
        c=toupper(c);
        if (c=='Y') sign_up(v);
        else main_menu();
        return;
    }
    cout<<"Da dang nhap thanh cong!";
}
void employee_sign_in(){}
void main_menu(Vector <User>& v,User &cur_User){
    cout<<" ------------------------------ "<<endl;
    cout<<"|        Menu dang nhap        |"<<endl;
    cout<<" ------------------------------ "<<endl;
    cout<<"1.Dang nhap"<<endl;
    cout<<"2.Dang ky"<<endl;
    cout<<"3.Dang nhap voi tu cach nhan vien"<<endl;
    cout<<"Moi lua chon:";
    int choice;cin>>choice;
    cin.ignore();
    switch (choice){
    case 1:{
        User current_User;
        user_sign_in(current_User,v);
        current_User.user_menu();
        break;
    }
    case 2:
        sign_up(v);
        break;
    case 3:
        employee_sign_in();
        break;
    }
}