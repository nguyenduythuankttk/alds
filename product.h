#ifndef PRODUCT_H    
#define PRODUCT_H
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip> 
#include <map>
#include <stdlib.h>
#include "vector.h"
using namespace std;
class Product {
    private:
        string name;
        string id;
        int quantity;
        int price;
        string category;
    public:
        Product();
        Product(const string&,const string&, const int&,const int&, const string&);
        Product(const Product&);
        ~Product();
        int Get_Quantity() const;
        int Get_price() const;
        string Get_ID() const;
        string Get_Name() const;
        string Get_Cat() const;
        void Set_Quantity(const int&);
        void Set_ID(const string&);
        void Set_Name(const string&);
        void Set_Price(const int&);
        void Set_Cat(const string&);
        void readfile(Vector<Product>&);
        void savefile(const Vector<Product> &);
        Product& operator=(const Product&);
        Product& operator=(const Product *);
        bool Find_by_id(const string&,const Vector<Product>&) const;
        void Find_product(const Vector<Product>&,Vector <Product>&);
        void All_product(const Vector<Product>&,Vector <Product>&);
        void Show(const Vector <Product>&);
        void Subtract_Product(Vector <Product>&,const int &,const string&);
        void Add_Quantity(Vector<Product>&,const string&,const int&);
        void Add_Product(Vector<Product>&,const string&);
};
#endif