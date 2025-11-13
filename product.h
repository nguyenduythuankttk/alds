#pragma once
#include "library.h"
using namespace std;
class Product {
    private:
        string name;
        string category;
        string id;
        int price;
        int sold;
        int bought;

    public:
        Product();
        Product(const string&, const string&, const int&, const string&,const int&,const int&);
        Product(const Product&);
        ~Product();

        int Get_price() const;
        string Get_ID() const;
        string Get_Name() const;
        string Get_Cat() const;
        int Get_Bought() const;
        int Get_Sold() const;

        void Add_bought(const int&); 
        void Add_sold(const int&);

        void readfile(Vector<Product>&);
        void savefile(const Vector<Product>&);
    
        bool Find_by_id(const string&, const Vector<Product>&) const; 
        void Find_product(const Vector<Product>&, Vector<Product>&,const string&,const string&, int&,int&);
        void All_product(const Vector<Product>&, Vector<Product>&);
        void Show(const Vector<Product>&);
        void Add_Product(Vector<Product>&, const string&);
        Product& Find_byid(const string&, const Vector<Product>&);

    };

