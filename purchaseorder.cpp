#include "purchaseorder.h"
#include "customerorder.h"   
#include "library.h"         
#include "warehouse.h"       
#include "product.h"             
#include "employee.h" 
#include "chitietphieunhap.h"
#include <iomanip>
PurchaseOrder::PurchaseOrder(){this->sum=0;}
PurchaseOrder::~PurchaseOrder(){}
void PurchaseOrder::Readfile(Vector <PurchaseOrder>& v){
    ifstream file("phieunhap.txt");
    string sv;
    int i;

    while (getline(file,sv)){
        if (sv=="") continue;
        i=0;
        string s;
            PurchaseOrder p;
        stringstream sub(sv);
        while (getline(sub,s,',')){
            if (s=="") continue;
            if (i==0) p.id=stoi(s);
            else if(i==1) p.employeeID=stoi(s);
            else if (i==2) p.warehouseID=stoi(s);
            else if(i==3) p.date=s;
            else if(i==4) p.sum=stoi(s);
            i++;
        }
        v.push_back(p);
    }
}
void PurchaseOrder::Savefile(const Vector <PurchaseOrder>& v){
    ofstream file("phieunhap.txt");
    for (int i=0;i<v.getsize();i++){
        file<<v[i].id<<","<<v[i].employeeID<<","<<v[i].warehouseID<<","<<v[i].sum<<","<<v[i].sum<<"\n";
    }
}
int PurchaseOrder::GetID() const{
    return id;
}
void PurchaseOrder::Create_PurchaseOrder(Vector<PurchaseOrder>&v){
    this->employeeID=current_Employee.getEmployeeID();
    this->id=v.getsize();
    cout<<"Nhap ngay thang nam"
    
}
