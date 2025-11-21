#include "user.h"
#include "product.h"
#include "customerorder.h"
#include "warehouse.h"
#include <iomanip>
#include <fstream>
#include <sstream>
User::User(){}
User::User(const int&ID,const string& username,const string& password,const string &fullname,const string& phone,const string& email,const string &address):
    Person(username,password,fullname,phone,email,address),userID(ID){}
User::User(const User& other):Person(other){
    this->userID=other.userID;
}
User::~User(){}
void User::ShowInfo() const{
    cout<<"ID nguoi dung:"<<userID<<endl;
    cout<<"Ten tai khoan:"<<username<<endl;
    cout<<"Mat khau::"<<password<<endl;
    cout<<"Ho ten:"<<fullname<<endl;
    cout<<"SDT:"<<phone<<endl;
    cout<<"Email:"<<email<<endl;
    cout<<"Dia chi:"<<address<<endl;
}
void User::SetuserID(const int& ID){
    this->userID=ID;
}
string User::getAddress() const{ return address;}
string User::getFullname() const{ return fullname;}
string User::getPhone() const{ return phone;}
string User::getEmail() const{ return email;}
void User::readfile(Vector<User> &v){
    ifstream filename("user.txt");
    string line;
    while (getline(filename,line)){
        if (line=="") continue;
        stringstream sub(line);
        string token;
        User u;
        int idx=0;
        while (getline(sub,token,',')){
            switch(idx){
                case 0: u.SetuserID(stoi(token)); break;
                case 1: u.Setusername(token); break;
                case 2: u.Setpassword(token); break;
                case 3: u.SetFullname(token); break;
                case 4: u.SetPhone(token); break;
                case 5: u.SetEmail(token); break;
                case 6: u.SetAddress(token); break;
            }
            idx++;
        }
        v.push_back(u);
    }
}
void User::savefile(const Vector<User> &v) const{
    ofstream file("user.txt");
    for (int i=0;i<v.getsize();i++){
        file<<v[i].userID<<","<<v[i].username<<","<<v[i].password<<","<<v[i].getFullname()<<","<<v[i].getPhone()<<","<<v[i].getEmail()<<","<<v[i].getAddress()<<"\n";
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
    cout << "| 5 | Chon kho hang                          |\n";
    cout << "| 6 | Dang xuat                              |\n";
    cout << "----------------------------------------------\n";
    cout << "=> Moi lua chon (1-5): ";
    int choice;
    cin>>choice;cin.ignore();
    Product p;
    switch (choice){
        case 1: {
            Product p;
            Vector<Product> list;
            p.sx(inWarehouse, list);
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
                c.create_Order(CustomerOrder_List);
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
                c.create_Order(CustomerOrder_List);
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
                c.create_Order(CustomerOrder_List);
            }
            goto option;
            break;
        }
        case 4: {
            Vector <CustomerOrder> result;
            CustomerOrder tmp;
            tmp.order_by(CustomerOrder_List,result,current_User.GetID());
            if (result.getsize()==0){
                cout<<"[Thong bao] Ban chua co don hang nao.\n";
                cout<<"Nhan Enter de quay lai menu";
                string pause;getline(cin,pause);
                main_menu();
                break;
            }
            cout<<"\n=== DANH SACH HOA DON ===\n";
            cout<<left
                <<setw(6)<<"ID"
                <<setw(15)<<"Ngay"
                <<setw(15)<<"Kho"
                <<setw(15)<<"Tong tien"
                <<endl;
            cout<<string(51,'-')<<endl;
            for (int i=0;i<result.getsize();i++){
                cout<<left
                    <<setw(6)<<result[i].getID()
                    <<setw(15)<<result[i].GetDate()
                    <<setw(15)<<result[i].GetWarehouseID()
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
            break;
        }
        case 5:{
            choose_warehouse(a);
            break;
        }
        case 6:{
            main_menu();
            break;
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
