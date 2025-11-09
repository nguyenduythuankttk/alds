#include "map.h"
#include "vector.h"
#pragma once
using namespace std;
class PurchaseOrder{
    int id;
    int employeeID;
    int warehouseID;
    string date;
    Map<string,int> List;
    unsigned int sum;
    public:
        PurchaseOrder();
        ~PurchaseOrder();
        void Readfile(Vector <PurchaseOrder>&);
        void Savefile(const Vector <PurchaseOrder>&);
        void create_PurchaseOrder(Vector<PurchaseOrder>&);
        void show() const;
};