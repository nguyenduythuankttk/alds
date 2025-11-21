#pragma once
#include "library.h"
#include <string>
using namespace std;
class Product {
    private:
        string name;
        string category;
        string id;
        int price;
        int sold;
        int bought;
        string last_bought;
        string last_sold;

    public:
        Product();
        Product(const string&, const string&, const int&, const string&,const int&,const int&,const string&,const string&);
        Product(const Product&);
        ~Product();

        int Get_price() const;
        string Get_ID() const;
        string Get_Name() const;
        string Get_Cat() const;
        int Get_Bought() const;
        int Get_Sold() const;
        string Get_last_bought() const;
        string Get_last_sold() const;
        bool Is_Inventory_Product(const string& currentDate) const;

        void Set_price(const int&);
        void Set_last_bought(const string&);
        void Set_last_sold(const string&);


        void Add_bought(const int&); 
        void Add_sold(const int&);

        void readfile(Vector<Product>&);
        void savefile(const Vector<Product>&);
    
        bool Find_by_id(const string&, const Vector<Product>&) const; 
        void Find_product(const Vector<Product>&, Vector<Product>&,const string&,const string&, int&,int&);
        void All_product(const Vector<Product>&, Vector<Product>&);
        void Show(const Vector<Product>&);
        void showinfo() const;
        void Add_Product(Vector<Product>&, const string&);
        Product& Find_byid(const string&, const Vector<Product>&);
        void sx(const Vector<Product>& ,Vector <Product>&);
    };
