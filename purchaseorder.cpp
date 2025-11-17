#include "purchaseorder.h"
#include "customerorder.h"   
#include "library.h"         
#include "warehouse.h"       
#include "product.h"         
#include "user.h"     
#include "employee.h"  
#include <iomanip>
PurchaseOrder::PurchaseOrder(){
    this->sum=0;
}
PurchaseOrder::~PurchaseOrder(){}
void PurchaseOrder::create_PurchaseOrder(Vector<PurchaseOrder> &v){
    cout << "\n===== TAO PHIEU NHAP =====\n";   
    PurchaseOrder newOrder;
    newOrder.id=v.getsize();
    newOrder.employeeID=current_Employee.getEmployeeID();
    cout<<"Nhap ngay nhap:";getline(cin,newOrder.date);
    cout<<"Nhap ma kho:"; cin>> newOrder.warehouseID;cin.ignore();
    string idproduct;
    Product pr;
    int quantity;
    Warehouse w=a.Find_by_id(newOrder.warehouseID,Warehouse_List);
    cout<<"Nhap tung dong theo dinh dang: <ID> <SoLuong>. Nhap -1 de ket thuc.\n";
    cout<<"+--------------------------------+--------------------+\n";
    cout<<"| ID san pham (-1 = ket thuc)   | So luong           |\n";
    cout<<"+--------------------------------+--------------------+\n";
    string row;
    while (true) {
        cout<<"| ";
        getline(cin,row);
        if (row=="") continue;
        if (row=="-1") break;
        stringstream ss(row);
        if (!(ss>>idproduct)){
            cout<<"[Thong bao] Vui long nhap ID san pham.\n";
            continue;
        }
        if (idproduct=="-1") break;
        if (!(ss>>quantity)){
            cout<<"[Thong bao] Vui long nhap so luong sau ID.\n";
            continue;
        }
        if (quantity<=0){
            cout<<"[Thong bao] So luong phai lon hon 0.\n";
            continue;
        }

        if(!pr.Find_by_id(idproduct,Product_List)) {
            cout<<"San pham chua ton tai. Tao san pham moi? (Y/N): ";
            char choice;
            cin>>choice;cin.ignore();
            choice=toupper(choice);
            if (choice=='Y') {
                pr.Add_Product(Product_List,idproduct);
            } else {
                cout<<"Bo qua dong vua nhap.\n";
                continue;
            }
        }

        pr=pr.Find_byid(idproduct,Product_List);
        w.Add_Product(idproduct,quantity);
        Product tmp,p=tmp.Find_byid(idproduct,Product_List);
        p.Add_bought(quantity);

        newOrder.sum+=pr.Get_price()*quantity;
        newOrder.List.push_back(idproduct,quantity);

        cout<<"\nDanh sach san pham vua nhap:\n";
        cout<<"+--------------------------------+--------------------+\n";
        cout<<"| Ma san pham                   | So luong           |\n";
        cout<<"+--------------------------------+--------------------+\n";
        for (int idx=0; idx<newOrder.List.Get_Size(); idx++){
            cout<<"| "<<left<<setw(30)<<newOrder.List.getKey(idx)
                <<"| "<<setw(18)<<newOrder.List.getValue(idx)<<"|\n";
        }
        cout<<"+--------------------------------+--------------------+\n";
        cout<<right;
    }
    cout<<"Tong tien:"<<newOrder.sum<<endl;
    v.push_back(newOrder);
    cout<<"Da nhap thanh cong!Tro ve menu\n";
    Employee e;
    e.employee_menu();
}
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
            else if(i==2) p.date=s;
            else if(i==3) p.sum=stoi(s);
            else if (i==4) p.warehouseID=stoi(s);
            else {
                size_t p1=s.find(";");
                string id_product=s.substr(1,p1-1);
                int sl=stoi(s.substr(p1+1,s.length()-1-p1));
                p.List.push_back(id_product,sl);
            }
            i++;
        }
        v.push_back(p);
    }
}
void PurchaseOrder::Savefile(const Vector <PurchaseOrder>& v){
    ofstream file("phieunhap.txt");
    for (int i=0;i<v.getsize();i++){
        file<<v[i].id<<","<<v[i].employeeID<<","<<v[i].date<<","<<v[i].sum<<","<<v[i].warehouseID;
        for (int j=0;j<v[i].List.Get_Size();j++) {
            file<<",("<<v[i].List.getKey(j)<<";"<<v[i].List.getValue(j)<<")";
        }
        file<<"\n";
    }
}
void PurchaseOrder::show() const{
    clear_screen();
    cout << "\n===== PHIEU NHAP #" << this->id << " =====\n";
    cout << "Nhan vien ID: " << this->employeeID << " | Kho ID: " << this->warehouseID << endl;
    cout << "Ngay nhap: " << this->date << endl;

    if (this->List.Get_Size() == 0) {
        cout << "[Thong bao] Phieu nhap khong co san pham.\n";
        cout << "Tong tien: " << this->sum << endl;
        return;
    }

    cout << left
         << setw(5) << "STT"
         << setw(12) << "Ma SP"
         << setw(40) << "Ten san pham"
         << setw(10) << "So luong"
         << setw(12) << "Gia"
         << setw(15) << "Thanh tien"
         << endl;
    cout << string(94, '-') << endl;

    long long calculated = 0;
    for (int i=0;i<this->List.Get_Size();i++) {
        string productID = this->List.getKey(i);
        int quantity = this->List.getValue(i);

        string productName = "[Khong tim thay]";
        int unitPrice = 0;
        Product finder;
        try {
            Product p = finder.Find_byid(productID, Product_List);
            productName = p.Get_Name();
            unitPrice = p.Get_price();
        }
        catch (const runtime_error&) {
            productName += " (ID: " + productID + ")";
        }

        long long lineTotal = static_cast<long long>(unitPrice) * quantity;
        calculated += lineTotal;

        cout << left
             << setw(5) << i + 1
             << setw(12) << productID
             << setw(40) << productName
             << setw(10) << quantity
             << setw(12) << unitPrice
             << setw(15) << lineTotal
             << endl;
    }

    cout << string(94, '-') << endl;
    cout << left << setw(79) << "Tong tien" << calculated << endl;
    if (calculated != this->sum) {
        cout << "[Luu y] Tong tien luu tru: " << this->sum << endl;
    }
}
void PurchaseOrder::order_date(const Vector<PurchaseOrder>&v ,Vector<PurchaseOrder>&r,const string& date) const{
    for (int i=0;i<v.getsize();i++)
        if (v[i].date==date) r.push_back(v[i]);
    return;
}   
int PurchaseOrder::getsum() const{return this->sum;}
