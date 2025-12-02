#include "chitiethoadon.h"
#include "product.h"
#include<iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;


namespace {
string FindProductNameByID(const string& productID){
    for (int i=0;i<Product_List.getsize();i++){
        if (Product_List[i].Get_ID()==productID)
            return Product_List[i].Get_Name();
    }
    return "";
}
}

CTHD::CTHD() 
    : invoiceID(0), IDProduct(""), productName(""), quantity(0), Price(0), totalPrice(0) {}

CTHD::CTHD(int invoiceID, string IDProduct, string productName, int quantity, int Price)
    : invoiceID(invoiceID), IDProduct(IDProduct), productName(productName), quantity(quantity), Price(Price) {
    totalPrice = quantity * Price;
}


int CTHD::getInvoiceID() const { return invoiceID; }
string CTHD::getIDProduct() const { return IDProduct; }
string CTHD::getProductName() const { return productName; }
int CTHD::getQuantity() const { return quantity; }
int CTHD::getPrice() const { return Price; }
int CTHD::getTotalPrice() const { return totalPrice; }
// Hiển thị chi tiết hóa đơn
void CTHD::Show(int stt) const {
    if (stt != -1) {
        cout << setw(5) << stt << ". ";
    }
    cout << left << setw(12) << IDProduct
         << left << setw(25) << (productName.empty()?"[Dang cap nhat]":productName)
         << left << setw(12) << quantity
         << left << setw(15) << Price
         << left << setw(15) << totalPrice
         << endl;
}
void CTHD::Readfile(Vector <CTHD>&v){
    ifstream file("hoadon.txt");
    string line;
    while (getline(file,line)){
        CTHD c;
        if (line=="") continue;
        vector<string> tokens;
        string token;
        stringstream sub(line);
        while (getline(sub,token,',')) tokens.push_back(token);
        if (tokens.size()<5) continue;
        size_t idx=0;
        c.invoiceID=stoi(tokens[idx++]);
        if (idx<tokens.size()) c.IDProduct=tokens[idx++];
        if (tokens.size()==5) c.productName=FindProductNameByID(c.IDProduct);
        else if (idx<tokens.size()) c.productName=tokens[idx++];
        if (idx<tokens.size()) c.quantity=stoi(tokens[idx++]);
        if (idx<tokens.size()) c.Price=stoi(tokens[idx++]);
        if (idx<tokens.size()) c.totalPrice=stoi(tokens[idx++]);
        if (c.productName.empty()) c.productName=FindProductNameByID(c.IDProduct);
        v.push_back(c);
    }
}
void CTHD::Savefile(const Vector<CTHD>&v) const{
    ofstream file("hoadon.txt");
    for (int i=0;i<v.getsize();i++){
        file<<v[i].invoiceID<<","<<v[i].IDProduct<<","<<v[i].productName<<","<<v[i].quantity<<","<<v[i].Price<<","<<v[i].totalPrice<<"\n";
    }
}
