#include "chitietphieunhap.h"
#include <fstream>
#include <sstream>
ChitietPhieunhap::ChitietPhieunhap(){}
ChitietPhieunhap::~ChitietPhieunhap(){}
void ChitietPhieunhap::SaveFile(const Vector <ChitietPhieunhap>& v) const{
    ofstream file("chitietphieunhap.txt");
    for (int i=0;i<v.getsize();i++){
        file<<v[i].id<<","<<v[i].idProduct<<","<<v[i].donGia<<","<<v[i].soLuong<<","<<v[i].tongTien<<"\n";
    }
    file.close();
}
void ChitietPhieunhap::ReadFile(Vector <ChitietPhieunhap>& v){
    ifstream file("chitietphieunhap.txt");
    string s;
    while (getline(file,s)){
        if (s=="") continue;
        string t;
        ChitietPhieunhap cp;
        stringstream sub(s);
        int i=0;
        while (getline(sub,s,',')){
            if (i==0) cp.id=stoi(s);
            else if (i==1) cp.idProduct=s;
            else if (i==2) cp.donGia=stoi(s);
            else if (i==3) cp.soLuong=stoi(s);
            else if (i==4) cp.tongTien=stoi(s);
        }
    }
}
int ChitietPhieunhap::TongTien() const{return this->donGia*this->soLuong;}