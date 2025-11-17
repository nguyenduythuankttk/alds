#include "user.h"
#include "product.h"
#include "customerorder.h"
#include "warehouse.h"
#include <iomanip>
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
    clear_screen();
    cout << "\n==============================================\n";
    cout << "|                MENU NGUOI DUNG             |\n";
    cout << "==============================================\n";
    cout << "| 1 | San pham noi bat                       |\n";
    cout << "| 2 | Danh sach san pham                     |\n";
    cout << "| 3 | Tim kiem san pham                      |\n";
    cout << "| 4 | Tra cuu don hang                       |\n";
    cout << "| 5 | Dang xuat                              |\n";
    cout << "----------------------------------------------\n";
    cout << "=> Moi lua chon (1-5): ";
    int choice;
    cin>>choice;cin.ignore();
    Product p;
    switch (choice){
        case 1: {
            Product p;
            Vector<Product> list;
            p.sx(Product_List, list);
            int lc;

            cout << "\n=== SAN PHAM NOI BAT (TOP 5) ===\n";
            if (list.getsize() == 0) {
                cout << "Khong co san pham nao.\n";
                break;
            }

            cout << left
                << setw(5) << "STT"
                << setw(30) << "Ten san pham"
                << setw(20) << "Loai"
                << setw(12) << "Gia"
                << setw(10) << "Da ban"
                << endl;
            cout << string(77, '-') << endl;

            int limit = min(list.getsize(), 5);
            for (int i = 0; i < limit; i++) {
                cout << left
                     << setw(5) << i + 1
                     << setw(30) << list[i].Get_Name()
                     << setw(20) << list[i].Get_Cat()
                     << setw(12) << list[i].Get_price()
                     << setw(10) << list[i].Get_Sold()
                     << endl;
            }
            
            
            cout<<"1.Mua hang\n";
            cout<<"2.Quay lai\n";
            cout<<"=> Moi lua chon: ";cin>>lc;cin.ignore();
            if (lc==2)  {
                inWarehouse.Erase();
               goto option;
            }
            else {
                CustomerOrder c;
                c.Create_Order(inWarehouse,CustomerOrder_List);
            }
            break;
        }

        case 2: {
            Product p;
            int lc;
            p.Show(inWarehouse);
            cout<<"1.Mua hang\n";
            cout<<"2.Quay lai\n";
            cout<<"=> Moi lua chon: ";cin>>lc;cin.ignore();
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
        case 3:{
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
            p.Find_product(inWarehouse,result,name,category,min,max);
            p.Show(result);
            int lc;
            cout<<"1.Mua hang\n";
            cout<<"2.Quay lai\n";
            cout<<"=> Moi lua chon: ";cin>>lc;cin.ignore();
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
        case 4: {
            Vector <CustomerOrder> result;
            CustomerOrder tmp;
            tmp.order_by(current_User,CustomerOrder_List,result);
            for (int i=0;i<result.getsize();i++){
                result[i].show();
            }
            string s;
            cout<<"Nhap phim bat ki de quay lai menu";getline(cin,s);
            main_menu();
            break;
        }
        case 5:{
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
