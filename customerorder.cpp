#include "customerorder.h"
#include "library.h"        
#include "warehouse.h"       
#include "product.h"         
#include "user.h"
#include "chitiethoadon.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <vector>
CustomerOrder::CustomerOrder(){
    this->id=0;
    this->customerID=0;
    this->orderDate="";
    this->sum=0;
    this->warehouseID=0;
}
CustomerOrder::~CustomerOrder(){}
void CustomerOrder::Readfile(Vector <CustomerOrder>& v){
    ifstream file("order.txt");
    string sv;
    while (getline(file,sv)){
        if (sv=="") continue;
        CustomerOrder c;
        vector<string> tokens;
        stringstream sub(sv);
        string s;
        while (getline(sub,s,',')){
            if (s=="") continue;
            tokens.push_back(s);
        }
        int idx=0;
        try{
            if (idx<tokens.size()) c.id=stoi(tokens[idx++]);
            if (idx<tokens.size()) c.customerID=stoi(tokens[idx++]);
            if (idx<tokens.size()){
                if (tokens[idx].find('/')==string::npos){
                    c.warehouseID=stoi(tokens[idx]);
                    idx++;
                } else {
                    c.warehouseID=0;
                    c.orderDate=tokens[idx];
                    idx++;
                }
            }
            if (idx<tokens.size() && c.orderDate.empty()) c.orderDate=tokens[idx++];
            if (idx<tokens.size()) c.sum=stoi(tokens[idx++]);
        }catch(const invalid_argument&){
            continue;
        }
        v.push_back(c);
    }
}
void CustomerOrder::Savefile(const Vector<CustomerOrder> &v) const{
    ofstream file("order.txt");
    for (int i=0;i<v.getsize();i++){
        file<<v[i].id<<","<<v[i].customerID<<","<<v[i].warehouseID<<","<<v[i].orderDate<<","<<v[i].sum;
        file<<"\n";
    }
}

void CustomerOrder::order_by(const Vector <CustomerOrder>& v,Vector <CustomerOrder>&result,int userID) const{
    for (int i=0;i<v.getsize();i++){
        if (v[i].customerID==userID) result.push_back(v[i]);
    }
}

void CustomerOrder::order_date(const Vector<CustomerOrder>& v,Vector<CustomerOrder>&r,const string&date) const{
    for (int i=0;i<v.getsize();i++)
        if (v[i].orderDate==date) r.push_back(v[i]);
    return;
}
int CustomerOrder::getsum() const{
    return this->sum;
}
string CustomerOrder::GetDate() const{ return this->orderDate;}
int CustomerOrder::GetWarehouseID() const {return this->warehouseID;}
int CustomerOrder::getID() const {return this->id;}
int CustomerOrder::GetCustomerID() const{return this->customerID;}
void CustomerOrder::create_Order(Vector <CustomerOrder>&v){
    clear_screen();
    CustomerOrder newOrder;
    newOrder.id=v.getsize();
    newOrder.customerID=current_User.GetID();
    newOrder.warehouseID=a.Get_ID();
    do{
        cout<<"Nhap ngay thang nam (dd/mm/yyyy): ";
        getline(cin,newOrder.orderDate);
        if (!_date(newOrder.orderDate)) cout<<"[Thong bao] Ngay khong hop le. Vui long nhap lai.\n";
    }while(!_date(newOrder.orderDate));

    cout<<"Nhap tung dong theo dinh dang: <MaSP> <SoLuong>. Nhap -1 de ket thuc.\n";
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
        if (!(ss>>productID)){
            cout<<"[Thong bao] Vui long nhap ma san pham.\n";
            continue;
        }
        if (productID=="-1") break;
        if (!(ss>>quantity)){
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
            productPtr=&finder.Find_byid(productID,Product_List);
        }catch(const runtime_error&){
            productPtr=nullptr;
        }
        if (!productPtr){
            cout<<"[Thong bao] San pham khong ton tai.\n";
            continue;
        }
        int stock=a.Get_Quantity(productID);
        if (stock==0){
            cout<<"[Thong bao] San pham dang het hang trong kho.\n";
            continue;
        }
        if (quantity>stock){
            cout<<"[Thong bao] Chi con "<<stock<<" san pham. Vui long nhap lai.\n";
            continue;
        }

        int unitPrice=productPtr->Get_price();
        a.Remove_Product(productID,quantity);
        productPtr->Add_sold(quantity);
        productPtr->Set_last_sold(newOrder.orderDate);
        long long lineTotal=static_cast<long long>(unitPrice)*quantity;
        newOrder.sum+=lineTotal;
        dshoadon.push_back(CTHD(newOrder.id,productID,quantity,unitPrice));
        hasItem=true;
        cout<<"Da them: "<<productID<<" x"<<quantity<<" (Gia "<<unitPrice<<")\n";
    }

    if (!hasItem){
        cout<<"[Thong bao] Chua co san pham nao duoc chon. Huy don.\n";
        return;
    }

    v.push_back(newOrder);
    a.ProductList(inWarehouse);
    cout<<"[Thong bao] Tao don hang thanh cong! Tong tien: "<<newOrder.sum<<"\n";
}

void CustomerOrder::show() const{
    cout<<"\n===== HOA DON #" << this->id << " =====\n";
    cout<<"Ngay lap : "<<this->orderDate<<"\n";
    User viewer;
    string customerName = "[Chua xac dinh]";
    for (int i=0;i<User_List.getsize();i++){
        if (User_List[i].GetID()==this->customerID){
            customerName = User_List[i].getFullname();
            break;
        }
    }
    cout<<"Khach hang: "<<customerName<<" (ID "<<this->customerID<<")\n";
    cout<<"Kho giao  : "<<this->warehouseID<<"\n";
    cout<<"Tong tien : "<<this->sum<<"\n";

    cout<<left
        <<setw(5)<<"STT"
        <<setw(20)<<"Ma SP"
        <<setw(12)<<"So luong"
        <<setw(15)<<"Don gia"
        <<setw(15)<<"Thanh tien"
        <<endl;
    cout<<string(67,'-')<<endl;
    bool found=false;
    int stt=1;
    for (int i=0;i<dshoadon.getsize();i++){
        if (dshoadon[i].getInvoiceID()==this->id){
            dshoadon[i].Show(stt++);
            found=true;
        }
    }
    if (!found){
        cout<<"(Khong co chi tiet san pham)\n";
    }
}
