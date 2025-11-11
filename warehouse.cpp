#include "warehouse.h"
#include "library.h"
#include "product.h"
Warehouse::Warehouse(){}
Warehouse::~Warehouse(){}
Warehouse::Warehouse(const int&id, const string& name,const string& address):id(id),address(address),name(name){}
void Warehouse::readfile(Vector <Warehouse> &v){
    ifstream file("warehouse.txt");
    string s;
    int i;
    while (getline(file,s)){
        if (s=="") continue;
        Warehouse w;
        stringstream sub(s);
        i=0;
        while (getline(sub,s,',')){
            if (i==0) w.id=stoi(s);
            else if (i==2) w.address=s;
            else if (i==1)w.name=s;
            else{
                size_t p1=s.find(";");
                string id_product=s.substr(1,p1-1);
                int sl=stoi(s.substr(p1+1,s.length()-1-p1));
                w.Inventory.push_back(id_product,sl);
            }
            i++;
        }
        v.push_back(w);
    }
}
void Warehouse::savefile(const Vector<Warehouse> &v){
    ofstream file("warehouse.txt");
    for (int i=0;i<v.getsize();i++){
        file<<v[i].id<<","<<v[i].name<<","<<v[i].address<<"\n";
        for (int j=0;j<v[i].Inventory.Get_Size();j++) {
            file<<",("<<v[i].Inventory.getKey(j)<<";"<<v[i].Inventory.getValue(j)<<")";
        }
    }
}
Warehouse& Warehouse::Find_by_id(const int& id,const Vector<Warehouse>& v){
    for (int i=0;i<v.getsize();i++ ){
        if (v[i].id==id) return v[i];
    }
    return v[0];
}
int Warehouse::Get_Quantity(const string& productID) const{
    for (int i=0;i<Inventory.Get_Size();i++){
        if (Inventory.getKey(i)==productID) return Inventory.getValue(i);
    }
    return 0;
}
void Warehouse::Add_Product(const string& productID, const int &qty){
    for (int i=0;i<Inventory.Get_Size();i++){
        if (Inventory.getKey(i)==productID) {
            Inventory.addValue(i,qty);
            return;
        }
    }
    Inventory.push_back(productID,qty); 
}
void Warehouse::Remove_Product(const string& productID, const int &qty){
    for (int i=0;i<Inventory.Get_Size();i++){
        if (Inventory.getKey(i)==productID) {
            Inventory.removeValue(i,qty);
            return;
        }
    }
}
Warehouse& Warehouse::Find_by_Address(const Vector<Warehouse>& v,const string& address) const {
    for (int i=0;i<v.getsize();i++) 
        if (address==v[i].address) return v[i];
    return v[0];
}
void Warehouse::ProductList(Vector<Product>& inWarehouse ) {
    for (int i=0;i<this->Inventory.Get_Size();i++){
        Product p;
        string id=this->Inventory.getKey(i);
        Product temp=p.Find_byid(id,Product_List);
        inWarehouse.push_back(temp);
    }
}
int Warehouse::Get_quantity(const string&ID) const{
    for (int i=0;i<this->Inventory.Get_Size();i++){
        if (this->Inventory.getKey(i)==ID) return Inventory.getValue(i);
    }
    return 0;
}