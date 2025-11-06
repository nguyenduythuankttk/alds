#include "warehouse.h"
#include <fstream>
#include <sstream>
Warehouse::Warehouse(){}
Warehouse::Warehouse(const int&id, const string& cat,const string& location):id(id),cat(cat),location(location){}
int Warehouse::Get_ID() const {return id;}
string Warehouse::Get_Cat() const {return cat;}
string Warehouse::Get_Location() const {return location;}
void Warehouse::Set_Cat(const string& cat) {
    this->cat=cat;
}
void Warehouse::Set_ID(const int& id){
    this->id=id;
}
void Warehouse::Set_Location(const string& location){
    this->location=location;
}
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
            else if (i==1) w.cat=s;
            else w.location=s;
            i++;
        }
        v.push_back(w);
    }
}
void Warehouse::savefile(const Vector<Warehouse> &v){
    ofstream file("warehouse.txt");
    for (int i=0;i<v.getsize();i++){
        file<<v[i].id<<","<<v[i].cat<<","<<v[i].location<<"\n";
    }
}