#include "product.h"
class Product_quantity{
    private:
        string id_product;
        int bought;
        int sold;
    public:
        int get_bought() const;
        int get_sold() const;
        void add_bought(const int&);
        void add_sold(const int&);
        Product_quantity();
        ~Product_quantity();
        Product_quantity& find_by_id(const string&);
};