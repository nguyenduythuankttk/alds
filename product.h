#pragma once
#include "library.h"
using namespace std;

class Product {
private:
    string name;
    string id;
    int price;
    string category;

public:
    Product();
    Product(const string&, const string&, const int&, const string&);
    Product(const Product&);
    ~Product();

    int Get_price() const;
    string Get_ID() const;
    string Get_Name() const;
    string Get_Cat() const;

    void Set_ID(const string&);
    void Set_Name(const string&);
    void Set_Price(const int&);
    void Set_Cat(const string&);

    void readfile(Vector<Product>&);
    void savefile(const Vector<Product>&);

    Product& operator=(const Product&);
    Product& operator=(const Product*);
    bool Find_by_id(const string&, const Vector<Product>&) const; 
    void Find_product(const Vector<Product>&, Vector<Product>&,const string&,const string&, int&,int&);
    void All_product(const Vector<Product>&, Vector<Product>&);
    void Show(const Vector<Product>&);
    void Add_Product(Vector<Product>&, const string&);
    bool operator<(const Product&) const;
    Product& Find_byid(const string&, const Vector<Product>&);

};

