#include "chitietphieunhap.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
using namespace std;
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
        ChitietPhieunhap cp;
        stringstream sub(s);
        int i=0;
        while (getline(sub,s,',')){
            if (i==0) cp.id=stoi(s);
            else if (i==1) cp.idProduct=s;
            else if (i==2) cp.donGia=stoi(s);
            else if (i==3) cp.soLuong=stoi(s);
            else if (i==4) cp.tongTien=stoi(s);
            i++;
        }
        v.push_back(cp);
    }
}
void ChitietPhieunhap::SetDetail(const int& orderID, const string& productID, const int& qty, const int& price){
    id=orderID;
    idProduct=productID;
    soLuong=qty;
    donGia=price;
    tongTien=qty*price;
}
int ChitietPhieunhap::GetID() const{return id;}
string ChitietPhieunhap::GetProductID() const{return idProduct;}
int ChitietPhieunhap::GetSoLuong() const{return soLuong;}
int ChitietPhieunhap::GetDonGia() const{return donGia;}
int ChitietPhieunhap::TongTien() const{return this->donGia*this->soLuong;}
void ChitietPhieunhap::show(const Vector<ChitietPhieunhap>& v, int orderID){
    cout<<"\n--- CHI TIET PHIEU NHAP #"<<orderID<<" ---\n";
    cout<<left
        <<setw(12)<<"Ma SP"
        <<setw(10)<<"So luong"
        <<setw(12)<<"Gia nhap"
        <<setw(14)<<"Thanh tien"
        <<endl;
    cout<<string(48,'-')<<endl;
    bool found=false;
    for (int i=0;i<v.getsize();i++){
        if (v[i].id==orderID){
            cout<<left
                <<setw(12)<<v[i].idProduct
                <<setw(10)<<v[i].soLuong
                <<setw(12)<<v[i].donGia
                <<setw(14)<<v[i].tongTien
                <<endl;
            found=true;
        }
    }
    if (!found){
        cout<<"(Khong co chi tiet cho phieu nay)\n";
    }
}
