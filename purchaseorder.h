#pragma once
#pragma once
#include "map.h"
#include "vector.h"
#include <string>
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