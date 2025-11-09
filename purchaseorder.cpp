#include "purchaseorder.h"
#include "warehouse.h"
#include "global.cpp"
#include <sstream>
Warehouse a;
PurchaseOrder::PurchaseOrder(){}
PurchaseOrder::~PurchaseOrder(){}
void PurchaseOrder::create_PurchaseOrder(Vector<PurchaseOrder> &v){
    cout << "\n===== TAO PHIEU NHAP =====\n";   
    this->id=v.getsize();
    cout<<"Nhap ID nhan vien:";cin>>this->employeeID;
    cout<<"Nhap ngay nhap";cin>>this->date;
    cout<<"Nhap ma kho"; cin>> this->warehouseID;
    int i=0;
    string idproduct;
    Product pr;
    int quantity;
    Warehouse w=a.Find_by_id(this->warehouseID,Warehouse_List);
    cout<<"Nhap danh sach san pham nhap.Nhap -1 de ket thuc qua trinh nhap";
    do {
        id:
        cout<<"Nhap ID san pham:";cin>>idproduct;
        if (idproduct=="-1") break;
        if(pr.Find_by_id(idproduct,Product_List)) {
            cout<<"Nhap so luong san pham:";cin>>quantity;
            w.Add_Product(idproduct,quantity);
        }
        else {
            cout<<"San pham chua ton tai.Tao san pham moi?(Y/N)";
            char choice;
            cin>>choice;
            choice=toupper(choice);
            if (choice=='Y') pr.Add_Product(Product_List,idproduct);
            else goto id;
            cout<<"Nhap so luong san pham:";cin>>quantity;
            w.Add_Product(idproduct,quantity);
        }
        pr=pr.Find_byid(idproduct,Product_List);
        this->sum+=pr.Get_price()*quantity;
        i++;
        List.push_back(idproduct,quantity);
    } while (idproduct!="-1");
    cout<<"Da nhap thanh cong!";
}
void PurchaseOrder::Readfile(Vector <PurchaseOrder>& v){
    ifstream file("phieunhap.txt");
    string s;
    int i;
    PurchaseOrder p;
    while (getline(file,s)){
        if (s=="") continue;
        i=0;
        stringstream sub(s);
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
    cout<<"THONG TIN PHIEU NHAP:\n";
    cout<<"ID phieu nhap:"<<this->id<<"\n";
    cout<<"ID nhan vien:"<<this->employeeID<<"\n";
    cout<<"ID kho"<<this->warehouseID<<"\n";
    cout<<"Ngay nhap:"<<this->date<<"\n";
    cout<<"Danh sach san pham:\n";
    for (int i=0;i<this->List.Get_Size();i++) {
        cout<<this->List.getKey(i)<<"  SL: "<<this->List.getValue(i)<<endl;
    }
    cout<<"Tong tien:"<<this->sum<<"\n";
}
