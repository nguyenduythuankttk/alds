#include "product.h"
#include <sstream>
#include <limits.h>
#include <iomanip>
#include <tuple>
#include <vector>
Product::Product() : price(0), import_price(0), sold(0), bought(0) {}
Product::Product(const string &Name, const string &id, const int &price, const int &importPrice, const string &cat,const int&nhap,const int&ban,const string& last1,const string& last2)
    : price(price), import_price(importPrice), category(cat), name(Name), id(id), bought(nhap), sold(ban),last_bought(last1),last_sold(last2) {}
Product::Product(const Product& p) {
    this->price = p.price;
    this->import_price = p.import_price;
    this->id = p.id;
    this->name = p.name;
    this->category = p.category;
    this->sold=p.sold;
    this->bought=p.bought;
}
Product::~Product() {}

string Product::Get_last_bought() const{return this->last_bought;}
string Product::Get_last_sold() const{return this->last_sold;}
void Product::Set_last_bought(const string& date){ this->last_bought=date; }
void Product::Set_last_sold(const string& date){ this->last_sold=date; }
bool Product::Is_Inventory_Product(const string& currentDate) const{
    auto monthsBetween=[&](const string& from,const string& to){
        int start[3]={0,0,0};
        int end[3]={0,0,0};
        if (!parse_date(from,start) || !parse_date(to,end)) return INT_MAX;
        int months=(end[2]-start[2])*12+(end[1]-start[1]);
        if (end[0]<start[0]) months--;
        return months;
    };
    int monthsSinceBought=monthsBetween(last_bought,currentDate);
    int monthsSinceSold=monthsBetween(last_sold,currentDate);
    return (monthsSinceBought>=6) || (monthsSinceSold>=6);
}
string Product::Get_ID() const { return this->id; }
string Product::Get_Name() const { return this->name; }
string Product::Get_Cat() const { return this->category; }
int Product::Get_price() const { return this->price; }
int Product::Get_import_price() const { return this->import_price; }
int Product::Get_Bought() const{return this->bought;}
int Product::Get_Sold() const {return this->sold;} 

void Product::Set_price(const int& price) {
    this->price=price;
    for (int i=0;i<Product_List.getsize();i++)
        if (Product_List[i].id==this->id) Product_List[i]=*(this);
}
void Product::Set_import_price(const int& price) {
    this->import_price=price;
    for (int i=0;i<Product_List.getsize();i++)
        if (Product_List[i].id==this->id)
            Product_List[i]=*(this);
}
void Product::Add_sold(const int& qty){
    this->sold+=qty;
    for (int i=0;i<Product_List.getsize();i++) 
        if (Product_List[i].id==this->id) 
            Product_List[i]=*(this);
}
void Product::Add_bought(const int& qty){
    this->bought+=qty;
    for (int i=0;i<Product_List.getsize();i++) 
        if (Product_List[i].id==this->id) 
            Product_List[i]=*(this);
}

bool Product::Find_by_id(const string& id, const Vector<Product>& v) const {
    for (int i = 0; i < v.getsize(); i++)
        if (id == v[i].Get_ID()) return true;
    return false;
}
Product& Product::Find_byid(const string& ID, const Vector<Product>& v) {
    for (int i = 0; i < v.getsize(); i++) {
        if (ID == v[i].Get_ID())
            return v[i];
    }
    throw runtime_error("Product not found");
}

void Product::All_product(const Vector<Product>& v, Vector<Product>& n) {
    for (int i = 0; i < v.getsize(); i++) n.push_back(v[i]);
}

void Product::Show(const Vector<Product>& v) {
    clear_screen();
    if (v.getsize() == 0) {
        cout << "[Thong bao] Danh sach san pham trong." << endl;
        return;
    }

    cout << left
         << setw(4) << "STT"
         << setw(12) <<"ID"
         << setw(30) << "Ten san pham"
         << setw(20) << "Loai"
         << setw(12) << "Gia"
         << setw(10) << "Da ban"
         << endl;
    cout << string(100, '-') << endl;

    for (int i = 0; i < v.getsize(); i++) {
        cout << left
             << setw(4) << i+1
             << setw(12) << v[i].id
             << setw(30) << v[i].Get_Name()
             << setw(20) << v[i].Get_Cat()
             << setw(12) << v[i].Get_price()
             << setw(10) << v[i].Get_Sold()
             << endl;
    }
}

void Product::showinfo() const {
    cout << left 
         << setw(30) << this->name
         << setw(20) << this->category
         << setw(12) << this->price
         << setw(10) << this->sold
         << endl;
}

void Product::savefile(const Vector<Product>& v) {
    ofstream file("product.txt");
    for (int i = 0; i < v.getsize(); i++) {
        file << v[i].id << "," 
             << v[i].name << "," 
             << v[i].category << "," 
             << v[i].price << ","
             << v[i].import_price << ","
             << v[i].sold << ","
             << v[i].bought << ","
             <<v[i].last_sold<<"," 
             <<v[i].last_bought<<"\n";
    }
}

void Product::readfile(Vector<Product>& v) {
    ifstream file("product.txt");
    string line;
    while (getline(file, line)) {
        if (line == "") continue;
        Product p;
        vector<string> tokens;
        string token;
        stringstream sub(line);
        while (getline(sub, token, ',')) tokens.push_back(token);
        if (tokens.size() < 4) continue;
        size_t idx = 0;
        p.id = tokens[idx++];
        if (idx < tokens.size()) p.name = tokens[idx++]; else p.name="";
        if (idx < tokens.size()) p.category = tokens[idx++]; else p.category="";
        if (idx < tokens.size()) {
            const string &val = tokens[idx++];
            p.price = val.empty()?0:stoi(val);
        } else p.price = 0;
        if (tokens.size() >= 9 && idx < tokens.size()) {
            const string &val = tokens[idx++];
            p.import_price = val.empty()?0:stoi(val);
        } else {
            p.import_price = p.price;
        }
        if (idx < tokens.size()) {
            const string &val = tokens[idx++];
            p.sold = val.empty()?0:stoi(val);
        } else p.sold = 0;
        if (idx < tokens.size()) {
            const string &val = tokens[idx++];
            p.bought = val.empty()?0:stoi(val);
        } else p.bought = 0;
        if (idx < tokens.size()) p.last_sold = tokens[idx++]; else p.last_sold="";
        if (idx < tokens.size()) p.last_bought = tokens[idx++]; else p.last_bought="";
        v.push_back(p);
    }
}

void Product::Add_Product(Vector<Product>& v, const string& ID) {
    cout << "\n===== THEM SAN PHAM MOI =====\n";
    this->id = ID;
    cout << "Nhap ten san pham: ";
    getline(cin, this->name);
    cout << "Nhap loai san pham: ";
    getline(cin, this->category);
    cout << "Nhap gia ban: ";
    cin >> this->price;
    cout << "Nhap gia nhap: ";
    cin >> this->import_price;
    cin.ignore();
    this->bought=0;
    this->sold=0;
    v.push_back(*this);

  /*  cout << "\nThong tin san pham vua them:\n";
    cout << "+--------------------------------+------------------------------+\n";
    cout << "| Truong                         | Gia tri                      |\n";
    cout << "+--------------------------------+------------------------------+\n";
    cout << "| Ma san pham                    | " << left << setw(28) << this->id << "|\n";
    cout << "| Ten san pham                   | " << left << setw(28) << this->name << "|\n";
    cout << "| Loai san pham                  | " << left << setw(28) << this->category << "|\n";
    cout << "| Gia (VND)                      | " << left << setw(28) << this->price << "|\n";
    cout << "| Da nhap                        | " << left << setw(28) << this->bought << "|\n";
    cout << "| Da ban                         | " << left << setw(28) << this->sold << "|\n";
    cout << "+--------------------------------+------------------------------+\n";
    cout << right;*/
}

/*bool Product::operator<(const Product& p) const {
    return this->id < p.id;
}*/


void Product::Find_product(const Vector<Product>&v, Vector<Product>& result,const string& name1,const string& category1, int& min_price,int& max_price){
    if (min_price==-1) min_price=0;
    if (max_price==-1) max_price=INT_MAX;
    if (max_price<min_price) swap(max_price,min_price);
    for (int i=0;i<v.getsize();i++){
        bool matchName = (name1=="-1") || timChuoi(name1, v[i].name);
        bool matchCat = (category1=="-1") || timChuoi(category1, v[i].category);
        if (matchName && matchCat && v[i].price>=min_price && v[i].price<=max_price)
            result.push_back(v[i]);
    }
}
void Product::sx(const Vector<Product> &v,Vector <Product> &r){
    for (int i=0;i<v.getsize();i++){
        r.push_back(v[i]);
    }
    int n=r.getsize();
    
    for (int i=0;i<n;i++)
        for (int j=i+1;j<n;j++){
            if (r[i].sold<r[j].sold){
                Product temp = r(i);
                r(i) = r(j);
                r(j) = temp;
            }
        }
}
