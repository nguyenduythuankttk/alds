#pragma once
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>
#include "vector.h"
#include "map.h"
    class Warehouse;
    class Product;
    class User;
    class Employee;
    class PurchaseOrder;
    class CustomerOrder;
    class ChitietPhieunhap;
    class CTHD;
    extern Vector<Warehouse> Warehouse_List;  
    extern Vector<Product> Product_List;
    extern Vector<Product> inWarehouse;
    extern Vector<User> User_List;
    extern Vector<Employee> Employee_List;
    extern Vector <PurchaseOrder> PurchaseOrder_List;
    extern Vector <CustomerOrder> CustomerOrder_List;
    extern Vector <ChitietPhieunhap> hoadon_List;
    extern Vector <CTHD> dshoadon;

    extern User current_User;
    extern Employee current_Employee;
    extern Warehouse a;

    void clear_screen();
    void main_menu();
    void sign_up(Vector <User>&);
    void user_sign_in(User &,Vector <User>&);
    void employee_sign_in();
    bool timChuoi(const string &, const string &);
    void choose_warehouse(Warehouse &);
    bool _date(const string&);