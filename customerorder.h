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
        int warehouseID;
        string orderDate;               // Ngày đặt hàng
        unsigned int sum;       // Tổng giá trị đơn hàng
    public:
        CustomerOrder();
        ~CustomerOrder();
        void Readfile(Vector <CustomerOrder>&);
        void Savefile(const Vector <CustomerOrder>&) const;
        int getID() const;
        int getsum() const;
        int GetWarehouseID() const;
        string GetDate() const;
        int GetUserID() const;
        void show() const;
        void order_date(const Vector<CustomerOrder>&,Vector<CustomerOrder> &,const string&) const;
        void create_Order(Vector<CustomerOrder>&);
        void order_by(const Vector<CustomerOrder>&,Vector<CustomerOrder>&,int userID) const;
};
