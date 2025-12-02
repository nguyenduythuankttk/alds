#include "purchaseorder.h"
#include "library.h"
#include "warehouse.h"
#include "product.h"
#include "employee.h"
#include "chitietphieunhap.h"
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cctype>
#include <iostream>

using namespace std;

PurchaseOrder::PurchaseOrder() : id(0), employeeID(0), warehouseID(0), sum(0) {}
PurchaseOrder::~PurchaseOrder() {}

void PurchaseOrder::Readfile(Vector<PurchaseOrder>& v){
    ifstream file("phieunhap.txt");
    string line;
    while (getline(file,line)){
        if (line=="") continue;
        stringstream sub(line);
        string s;
        PurchaseOrder order;
        int i=0;
        while (getline(sub,s,',')){
            if (s=="") continue;
            switch (i){
                case 0: order.id=stoi(s); break;
                case 1: order.employeeID=stoi(s); break;
                case 2: order.date=s; break;
                case 3: order.sum=stoul(s); break;
                case 4: order.warehouseID=stoi(s); break;
            }
            i++;
        }
        v.push_back(order);
    }
}

void PurchaseOrder::Savefile(const Vector<PurchaseOrder>& v){
    ofstream file("phieunhap.txt");
    for (int i=0;i<v.getsize();i++){
        file<<v[i].id<<","<<v[i].employeeID<<","<<v[i].date<<","<<v[i].sum<<","<<v[i].warehouseID<<"\n";
    }
}

int PurchaseOrder::GetID() const{return id;}
int PurchaseOrder::GetWarehouseID() const{return warehouseID;}
string PurchaseOrder::GetDate() const{return date;}
int PurchaseOrder::GetEmployeeID() const{return employeeID;}
int PurchaseOrder::getsum() const{return sum;}

void PurchaseOrder::create_PurchaseOrder(Vector<PurchaseOrder>& v){
    clear_screen();
    PurchaseOrder newOrder;
    newOrder.id = v.getsize();
    newOrder.employeeID = current_Employee.getEmployeeID();

    cout<<"===== TAO PHIEU NHAP =====\n";
    do{
        cout<<"Nhap ngay nhap (dd/mm/yyyy): ";
        getline(cin,newOrder.date);
        if (!_date(newOrder.date)) cout<<"[Thong bao] Ngay khong hop le. Vui long nhap lai.\n";
    } while(!_date(newOrder.date));
    cout<<"Nhap ma kho: ";
    cin>>newOrder.warehouseID;
    cin.ignore();

    Warehouse warehouse = a.Find_by_id(newOrder.warehouseID, Warehouse_List);

    cout<<"Nhap tung dong <MaSP> <SoLuong>. Nhap -1 de ket thuc.\n";
    cout<<"+--------------------------------+--------------------+\n";
    cout<<"| ID san pham (-1 = ket thuc)   | So luong           |\n";
    cout<<"+--------------------------------+--------------------+\n";

    string row;
    bool hasItem=false;
    while (true){
        cout<<"| ";
        getline(cin,row);
        if (row=="") continue;
        if (row=="-1") break;

        stringstream ss(row);
        string productID;
        int quantity;

        if(!(ss>>productID)){
            cout<<"[Thong bao] Vui long nhap ma san pham.\n";
            continue;
        }
        if (productID=="-1") break;
        if(!(ss>>quantity)){
            cout<<"[Thong bao] Vui long nhap so luong hop le.\n";
            continue;
        }
        if (quantity<=0){
            cout<<"[Thong bao] So luong phai lon hon 0.\n";
            continue;
        }

        Product finder;
        Product* productPtr=nullptr;
        try{
            productPtr = &finder.Find_byid(productID, Product_List);
        }catch(const runtime_error&){
            productPtr=nullptr;
        }

        if (!productPtr){
            cout<<"San pham chua ton tai. Tao san pham moi? (Y/N): ";
            char choice;
            cin>>choice;cin.ignore();
            choice=toupper(choice);
            if (choice!='Y'){
                cout<<"Bo qua dong vua nhap.\n";
                continue;
            }
            finder.Add_Product(Product_List, productID);
            productPtr = &finder.Find_byid(productID, Product_List);
        }

        int importPrice = productPtr->Get_import_price();
        warehouse.Add_Product(productID, quantity);
        productPtr->Add_bought(quantity);
        productPtr->Set_last_bought(newOrder.date);
        long long lineTotal = static_cast<long long>(importPrice)*quantity;
        newOrder.sum += lineTotal;

        ChitietPhieunhap detail;
        detail.SetDetail(newOrder.id, productID, quantity, importPrice);
        hoadon_List.push_back(detail);
        hasItem=true;

        cout<<"Da them: "<<productID<<" x"<<quantity<<" (Gia nhap "<<importPrice<<")\n";
    }

    if (!hasItem){
        cout<<"[Thong bao] Chua co san pham nao duoc nhap. Huy phieu.\n";
        return;
    }

    v.push_back(newOrder);
    cout<<"Da tao phieu nhap thanh cong! Tong tien: "<<newOrder.sum<<"\n";
}

void PurchaseOrder::show() const{
    cout<<"\n===== PHIEU NHAP #" << id << " =====\n";
    cout<<"Ngay nhap : "<<date<<"\n";
    string empName="[Chua xac dinh]";
    for (int i=0;i<Employee_List.getsize();i++){
        if (Employee_List[i].getEmployeeID()==employeeID){
            empName=Employee_List[i].GetFullname();
            break;
        }
    }
    cout<<"Nhan vien : "<<empName<<" (ID "<<employeeID<<")\n";
    cout<<"Kho nhap  : "<<warehouseID<<"\n";
    cout<<"Tong tien : "<<sum<<"\n";
}

void PurchaseOrder::order_date(const Vector<PurchaseOrder>& origin, Vector<PurchaseOrder>& result,const string& d) const{
    for (int i=0;i<origin.getsize();i++){
        if (origin[i].date==d) result.push_back(origin[i]);
    }
}
