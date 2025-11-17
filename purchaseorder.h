#pragma once
#pragma once
#include "map.h"
#include "vector.h"
#include <string>
using namespace std;

class PurchaseOrder{
    private:
        int id;
        int employeeID;
        int warehouseID;
        string date;
        unsigned int sum;
    public:
        PurchaseOrder();
        ~PurchaseOrder();
        void Readfile(Vector <PurchaseOrder>&);
        void Savefile(const Vector <PurchaseOrder>&);
        int GetID() const;
        void Create_PurchaseOrder(Vector <PurchaseOrder>&);
};