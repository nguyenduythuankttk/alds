#include "product.h"
#include <sstream>
#include <limits.h>
Product::Product() {}

Product::Product(const string &Name, const string &id, const int &price, const string &cat)
    : price(price), category(cat), name(Name), id(id) {}

Product::Product(const Product& p) {
    this->price = p.price;
    this->id = p.id;
    this->name = p.name;
    this->category = p.category;
}

Product::~Product() {}

string Product::Get_ID() const { return this->id; }
string Product::Get_Name() const { return this->name; }
string Product::Get_Cat() const { return this->category; }
int Product::Get_price() const { return this->price; }

void Product::Set_ID(const string& ID) { this->id = ID; }
void Product::Set_Name(const string& name) { this->name = name; }
void Product::Set_Price(const int& price) { this->price = price; }
void Product::Set_Cat(const string& cat) { this->category = cat; }

Product& Product::operator=(const Product* p) {
    this->price = p->price;
    this->id = p->id;
    this->name = p->name;
    this->category = p->category;
    return *this;
}

Product& Product::operator=(const Product& p) {
    this->price = p.price;
    this->id = p.id;
    this->name = p.name;
    this->category = p.category;
    return *this;
}

bool Product::Find_by_id(const string& id, const Vector<Product>& v) const {
    for (int i = 0; i < v.getsize(); i++)
        if (id == v[i].Get_ID()) return true;
    return false;
}

void Product::All_product(const Vector<Product>& v, Vector<Product>& n) {
    for (int i = 0; i < v.getsize(); i++) n.push_back(v[i]);
}

void Product::Show(const Vector<Product>& v) {
    for (int i = 0; i < v.getsize(); i++) 
        cout << v[i].id << " | " << v[i].name << " | " 
             << v[i].category << " | " << v[i].price << endl;
}

void Product::savefile(const Vector<Product>& v) {
    ofstream file("product.txt");
    for (int i = 0; i < v.getsize(); i++) {
        file << v[i].id << "," 
             << v[i].name << "," 
             << v[i].category << "," 
             << v[i].price << "\n";
    }
}

void Product::readfile(Vector<Product>& v) {
    ifstream file("product.txt");
    string s;
    int i;
    while (getline(file, s)) {
        Product p;
        if (s == "") continue;
        i = 0;
        stringstream sub(s);
        while (getline(sub, s, ',')) {
            if (i == 0) p.id = s;
            else if (i == 1) p.name = s;
            else if (i == 2) p.category = s;
            else if (i == 3) p.price = stoi(s);
            i++;
        }
        v.push_back(p);
    }
}

void Product::Add_Product(Vector<Product>& v, const string& ID) {
    cout << "Nhap ten san pham: ";
    getline(cin, this->name);
    cout << "Nhap loai san pham: ";
    getline(cin, this->category);
    this->id = ID;
    cout << "Nhap gia: ";
    cin >> this->price;
    cin.ignore(); // tránh lỗi getline sau cin
    v.push_back(*this);
}

bool Product::operator<(const Product& p) const {
    return this->id < p.id;
}

Product& Product::Find_byid(const string& ID, const Vector<Product>& v) {
    for (int i = 0; i < v.getsize(); i++) {
        if (ID == v[i].Get_ID())
            return v[i];
    }
    throw runtime_error("Product not found");
}
void Product::Find_product(const Vector<Product>&v, Vector<Product>&result,const string& name,const string& category, int& min_price,int& max_price){
    if (min_price==-1) min_price=0;
    if (max_price==-1) max_price=INT_MAX;
    if (max_price<min_price) swap(max_price,min_price);
    for (int i=0;i<v.getsize();i++){
        if ((name=="-1" || v[i].name==name) && (category=="-1" || v[i].category==category) && (v[i].price>=min_price) && (v[i].price<=max_price))
            result.push_back(v[i]);
    }

}