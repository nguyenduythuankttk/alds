#include "sold_product.h"
Product_quantity::Product_quantity(){}
Product_quantity::~Product_quantity(){}
void Product_quantity::add_bought(const int& qty){this->bought+=qty;}
void Product_quantity::add_sold(const int& qty){this->sold+=qty;}
int Product_quantity::get_bought() const{ return this->bought;}
int Product_quantity::get_sold() const{return this->sold;}
void Product_quantity::find_by_id(const string& id) const{
    for (int i=0;i<n;i++)
}