#include "user.h"
#include <fstream>
#include <sstream>
#include "product.h"
User::User(){}
User::User(const int&ID,const string& username,const string& password):
    Person(username,password),userID(ID){}
User::User(const User& other){
    this->userID=other.userID;
    this->username=other.username;
    this->password=other.password;
}
User::~User(){}
void User::ShowInfo() const{
    cout<<"ID nguoi dung:"<<userID<<endl;
    cout<<"Ten tai khoan:"<<username<<endl;
    cout<<"Mat khau::"<<password<<endl;
}
void User::SetuserID(const int& ID){
    this->userID=ID;
}
void User::readfile(Vector<User> &v){
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
void User::savefile(const Vector<User> &v) const{
    ofstream file("user.txt");
    for (int i=0;i<v.getsize();i++){
        file<<v[i].userID<<","<<v[i].username<<","<<v[i].password<<"\n";
    }
}
int User::GetID() const{
    return this->userID;
}
void User::user_menu(){
    option:
    cout<<" ------------------------------ "<<endl;
    cout<<"|             Menu             |"<<endl;
    cout<<" ------------------------------ "<<endl;
    cout<<"1.Hien thi danh sach san pham"<<endl;
    cout<<"2.Tim kiem san pham"<<endl;
    cout<<"3.Tra cuu don hang "<<endl;
    cout<<"4.Dang xuat"<<endl;
    int choice;
    cin>>choice;
    Product p;
    switch (choice){
        case 1: {
            p.All_product(Product_List,Find_result);
            p.Show(Find_result);
            int lc;
            cout<<"1.Quay lai menu"<<endl;
            cout<<"2.Tiep tuc mua hang"<<endl;
            cout<<"Moi lua chon:"<<endl;
            cin>>lc;
            if (lc==1) goto option;
            int sl=0,stt=0;
            map<Product,int> sanpham;
            cout<<"Nhap stt san pham"<<endl;
            cout<<"Nhap 0 de ket thuc"<<endl;
            do{
                cout<<"Nhap stt:";
                cin>>stt;
                slg:
                cout<<"Nhap so luong san pham";
                cin>>sl;
                if (p[stt-1].Get_slg()>sl) {
                    cout<<"San pham khong du so luong\n";
                    cout<<"Vui long giam so luong san pham can mua\n";
                    goto slg;
                }
                sanpham.insert(make_pair(p[stt-1],sl));
            } while (stt!=0);
            if (sanpham.empty()) goto option; else tonghang(sanpham);
            break;
        }
        case 2:{
            int price_min,price_max;
            string category;
            string product_name;
            cout<<"Moi nhap thong tin cua san pham muon tim\n";
            cout<<"Nhap -1 thay cho du lieu trong\n";
            cout<<"Nhap loai san pham:";
            cin>>category;
            cout<<"Nhap khoang gia:";
            cin>>price_min>>price_max;
            cin.ignore();
            if (price_min>price_max) swap(price_max,price_min);
            cout<<"Nhap ten san pham:";
            cin>>product_name;
            vector <Product> P;
            Product::Find_product(price_min,price_max,product_name,category,P);
            Product::Showproduct(P);
            break;
        }
        case 3: {

        }
        case 4:{
            Menu();
        }
        
    }
}