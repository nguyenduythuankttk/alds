#include "library.h"
using namespace std;
void readfile(ifstream &filename,Vector<User> &v){
    string s;
    int i;
    User u;
    ifstream filename("user.txt");
    while (getline(filename,s)){
        if (s=="") continue;
        i=0;
        stringstream sub(s);
        while (getline(sub,s,',')){
            if (i==0) u.SetuserID(stoi(s));
            else if(i==1) u.Setusername(s);
            else u.Setpassword(s);
            i++;
        }
        v.push_back(u);
    }
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
    u=User(v.getsize(),name,password);
    v.push_back(u);
    cout<<"Da tao tai khoan thanh cong";
}
void user_sign_in(User &cur_User,Vector <User>&v){
    string username,password;
    cout<<"Nhap ten dang nhap:";
    getline(cin,username);
    cout<<"Nhap mat khau:";
    getline(cin,password);
    for (int i=0;i<v.getsize();i++){
        if (v[i].Getpassword()==password && v[i].Getusername()==username){
            cur_User=v[i];
        }
    }
    cout<<"Da dang nhap thanh cong!";
}
void employee_sign_in();
void main_menu(Vector <User>& v,User &cur_User){
    cout<<" ------------------------------ "<<endl;
    cout<<"|        Menu dang nhap        |"<<endl;
    cout<<" ------------------------------ "<<endl;
    cout<<"1.Dang nhap"<<endl;
    cout<<"2.Dang ky"<<endl;
    cout<<"3.Dang nhap voi tu cach nhan vien"<<endl;
    cout<<"Moi lua chon:";
    int choice;cin>>choice;
    switch (choice){
    case 1:
        user_sign_in(cur_User,v);
        break;
    case 2:
        sign_up(v);
        break;
    case 3:
        employee_sign_in();
        break;
    }
}