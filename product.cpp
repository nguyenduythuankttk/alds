#include "product.h"
#include <sstream>
Product::Product(){};
Product::Product(const string &Name,const string &id,const int &quantity,const int &price,const string &cat)
    : quantity(quantity), price(price),category(cat),name(Name),id(id){
}
Product::Product(const Product& p) {
    this->price = p.price;
    this->id = p.id;
    this->name = p.name;
    this->category = p.category;
    this->quantity = p.quantity;
}
Product::~Product(){}
int Product::Get_Quantity() const{return this->quantity;}
string Product::Get_ID()const {return this->id;}
string Product::Get_Name()const {return this->name;}
string Product::Get_Cat() const {return this->category;}
int Product::Get_price() const {return this->price;}
void Product::Set_Quantity(const int& quantity){this->quantity=quantity;}
void Product::Set_ID(const string& ID){this->id=ID;}
void Product::Set_Name(const string& name){this->name=name;}
void Product::Set_Price(const int& price){this->price=price;}
void Product::Set_Cat(const string& cat){this->category=cat;}
Product& Product::operator=(const Product *p){
    this->price=p->price;
    this->id=p->id;
    this->name=p->name;
    this->category=p->category;   
    this->quantity=p->quantity;
    return *this;
}
Product& Product::operator=(const Product& p){
    this->price=p.price;
    this->id=p.id;
    this->name=p.name;
    this->category=p.category;   
    this->quantity=p.quantity;
    return *this;
}
bool Product::Find_by_id(const string&id,const Vector<Product>& v) const{
    for (int i=0;i<v.getsize();i++)
        if (id==v[i].Get_ID()) return true;
    return false;
}
void All_product(const Vector<Product>& v,Vector <Product>& n) {
    for (int i=0;i<v.getsize();i++) n.push_back(v[i]);
}
void Product::Show(const Vector<Product> &v){
    for (int i=0;i<v.getsize();i++) 
        cout<<v[i].id<<v[i].name<<v[i].category<<v[i].quantity<<v[i].price;
}
void Product::savefile(const Vector<Product>& v){
    ofstream file("product.txt");
    for (int i=0;i<v.getsize();i++){
        file<<v[i].id<<","<<v[i].name<<","<<v[i].category<<","<<v[i].quantity<<","<<v[i].price<<"\n";
    }
}
void Product::readfile(Vector <Product> &v){
    ifstream file("product.txt");
    string s;
    int i;
    while (getline(file,s)){
        Product p;
        if (s=="") continue;
        i=0;
        stringstream sub(s);
        while (getline(sub,s,',')){
            if (i==0) p.id=s;
            else if(i==1) p.name=s;
            else if (i==2) p.category=s;
            else if (i==3) p.quantity=stoi(s);
            else if (i==4) p.price=stoi(s);
            i++;
        }
        v.push_back(p);
    }
}
void Product::Subtract_Product(Vector <Product>&v ,const int& Quantity,const string& ID){
    for (int i=0;i<v.getsize();i++){
        if (ID==v[i].Get_ID()) v[i].quantity-=Quantity;
    }
}
void Product::Add_Quantity(Vector <Product>& v,const string& ID,const int& Quantity){
    for (int i=0;i<v.getsize();i++) 
        if (ID==v[i].Get_ID()) v[i].quantity+=Quantity;
}
void Product::Add_Product(Vector <Product>&v,const string& ID){
    cout<<"Nhap ten sp";
    getline(cin,this->name);
    cout<<"Nhap loai san pham";
    getline(cin,this->category);
    this->id=ID;
    cout<<"Nhap gia:";
    cin>>this->price;
    cout<<"Nhap so luong";
    cin>>this->quantity;
    v.push_back(*this);
}