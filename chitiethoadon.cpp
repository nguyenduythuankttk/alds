#include "chitiethoadon.h"
#include<iostream>
#include <sstream>
#include <fstream>
using namespace std;


CTHD::CTHD() 
    : invoiceID(0), IDProduct(""), quantity(0), Price(0), totalPrice(0) {}

CTHD::CTHD(int invoiceID, string IDProduct, int quantity, int Price)
    : invoiceID(invoiceID), IDProduct(IDProduct), quantity(quantity), Price(Price) {
    totalPrice = quantity * Price;
}


int CTHD::getInvoiceID() const { return invoiceID; }
string CTHD::getIDProduct() const { return IDProduct; }
int CTHD::getQuantity() const { return quantity; }
int CTHD::getPrice() const { return Price; }
int CTHD::getTotalPrice() const { return totalPrice; }
// Hiển thị chi tiết hóa đơn
void CTHD::Show(int stt) const {
    if (stt != -1) {
        cout << setw(5) << stt << ". ";
    }
    cout << left << setw(20) << IDProduct
         << left << setw(12) << quantity
         << left << setw(15) << Price
         << left << setw(15) << totalPrice
         << endl;
}
void CTHD::Readfile(Vector <CTHD>&v){
    ifstream file("hoadon.txt");
    string line;
    int i;
    while (getline(file,line)){
        i=0;
        stringstream sub(line);
        string s;
        CTHD c;
        while (getline(sub,s,',')){
            switch (i){
                case 0:{c.invoiceID=stoi(s);break;}
                case 1:{c.IDProduct=s;break;}
                case 2:{c.quantity=stoi(s);break;}
                case 3:{c.Price=stoi(s);break;}
                case 4:{c.totalPrice=stoi(s);break;}
            }
            i++;
        }
        v.push_back(c);
    }
}
void CTHD::Savefile(const Vector<CTHD>&v) const{
    ofstream file("hoadon.txt");
    for (int i=0;i<v.getsize();i++){
        file<<v[i].invoiceID<<","<<v[i].IDProduct<<","<<v[i].quantity<<","<<v[i].Price<<","<<v[i].totalPrice<<"\n";
    }
}
