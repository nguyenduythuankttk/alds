#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "vector.h"
using namespace std;

class CTHD {
private:
    int invoiceID;
    string IDProduct;
    int quantity;
    int Price;
    int totalPrice;

public:
    
    CTHD();
    CTHD(int invoiceID, string IDProduct, int quantity, int Price);
    int getInvoiceID() const;
    string getIDProduct() const;
    int getQuantity() const;
    int getPrice() const;
    int getTotalPrice() const;
    void Show(int = -1) const;
    void Readfile(Vector <CTHD>&);
    void Savefile(const Vector <CTHD>&) const;

};