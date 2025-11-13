#include "user.h"
#include "product.h"
#include "customerorder.h"
#include "warehouse.h"
User::User(){}
User::User(const int&ID,const string& username,const string& password,const string &address):
    Person(username,password),userID(ID),address(address){}
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
string User::getAddress() const{ return address;}
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
            else if(i==2) u.Setpassword(s);
            else u.address=s;
            i++;

        }
        v.push_back(u);
    }
}
void User::savefile(const Vector<User> &v) const{
    ofstream file("user.txt");
    for (int i=0;i<v.getsize();i++){
        file<<v[i].userID<<","<<v[i].username<<","<<v[i].password<<","<<v[i].address<<"\n";
    }
}
int User::GetID() const{
    return this->userID;
}
void User::user_menu() const{
    option:
    cout<<" ------------------------------ "<<endl;
    cout<<"|             Menu             |"<<endl;
    cout<<" ------------------------------ "<<endl;
    cout<<"1.Hien thi danh sach san pham"<<endl;
    cout<<"2.Tim kiem san pham"<<endl;
    cout<<"3.Tra cuu don hang "<<endl;
    cout<<"4.Dang xuat"<<endl;
    int choice;
    cin>>choice;cin.ignore();
    Product p;
    switch (choice){
        case 1: {
            Product p;
            int lc;
            Warehouse tmp;
            a=tmp.Find_by_Address(Warehouse_List,current_User.address);
            a.ProductList(inWarehouse);
            p.Show(inWarehouse);
            cout<<"1.Mua hang\n";
            cout<<"2.Quay lai\n";
            cout<<"Moi lua chon";cin>>lc;cin.ignore();
            if (lc==2)  {
                inWarehouse.Erase();
               goto option;
            }
            else {
                CustomerOrder c;
                c.Create_Order(inWarehouse,CustomerOrder_List);
            }
            inWarehouse.Erase();
            goto option;
            break;
        }
        case 2:{
            string name,category;
            int min,max;
            cout<<"Nhap thong tin san pham.Nhap '-1' de bo qua \n";
            cout<<"Ten san pham:";getline(cin,name);
            cout<<"Loai san pham:"; getline(cin,category);
            cout<<"Gia thap nhat";cin>>min;cin.ignore();
            cout<<"Gia cao nhat";cin>>max;cin.ignore();
            Product p;
            Vector <Product> result;
            Warehouse tmp;
            a=tmp.Find_by_Address(Warehouse_List,current_User.address);
            a.ProductList(inWarehouse);
            p.Find_product(inWarehouse,result,name,category,min,max);
            p.Show(result);
            int lc;
            cout<<"1.Mua hang\n";
            cout<<"2.Quay lai\n";
            cout<<"Moi lua chon";cin>>lc;cin.ignore();
            if (lc==2) {
                inWarehouse.Erase();
                goto option;
                
            }
            else {
                CustomerOrder c;
                c.Create_Order(result,CustomerOrder_List);
            }
            inWarehouse.Erase();
            goto option;
            break;
        }
        case 3: {
            Vector <CustomerOrder> result;
            CustomerOrder tmp;
            tmp.order_by(current_User,CustomerOrder_List,result);
            tmp.show();
            break;
        }
        case 4:{
            main_menu();
        }
    }
    return;
}
bool User::find_by_id(const int& id) const{
    for (int i=0;i<User_List.getsize();i++){
        if (id==User_List[i].userID) return true;
    }
    return false;
}
User& User::id(const int &ID) const{
    for (int i=0;i<User_List.getsize()-1;i++){
        if (ID==User_List[i].userID) return User_List[i];
    }
    return User_List[User_List.getsize()-1];
}