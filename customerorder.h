#pragma once
#pragma once
#include "map.h"
#include "vector.h"
#include <string>
using namespace std;
class Product;
class User;
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
        void Create_Order(const Vector <Product> &,Vector <CustomerOrder>&);
        void order_by(const User&, const Vector <CustomerOrder>&,Vector <CustomerOrder>&);
        void show() const;
        void order_date(const Vector<CustomerOrder>&,Vector<CustomerOrder>&,const string&) const;
        int getsum() const;
};
