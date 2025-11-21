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
        void create_PurchaseOrder(Vector <PurchaseOrder>&);
        void show() const;
        void order_date(const Vector<PurchaseOrder>&, Vector<PurchaseOrder>&, const string&) const;
        int getsum() const;
        int GetWarehouseID() const;
        string GetDate() const;
        int GetEmployeeID() const;
};
