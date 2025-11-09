#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "map.h"
#include "vector.h"
using namespace std;

class CustomerOrder {
    private:
        int id;                         // Mã đơn hàng của khách
        int customerID;                 // Mã khách hàng
        string orderDate;               // Ngày đặt hàng
        Map<string, int> productList;   // Danh sách sản phẩm: <ProductID, Quantity>
        unsigned int sum;       // Tổng giá trị đơn hàng

    public:
        CustomerOrder();
        CustomerOrder(const int&,const int&,const string&);
        CustomerOrder(const CustomerOrder&);
        ~CustomerOrder();
        void readFile(Vector<CustomerOrder>&);
        void saveFile(const Vector<CustomerOrder>&) const;
        void show() const;
};
