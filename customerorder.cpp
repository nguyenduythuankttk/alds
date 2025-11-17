#include "customerorder.h"
#include "library.h"        
#include "warehouse.h"       
#include "product.h"         
#include "user.h"       
#include <fstream>
#include <sstream>
#include <iomanip>
#include "library.h"
CustomerOrder::CustomerOrder(){
    this->id=0;
    this->customerID=0;
    this->orderDate="";
    this->sum=0;
}
CustomerOrder::CustomerOrder(const int& id,const int &userID,const string &date){
    this->id=id;
    this->customerID=userID;
    this->orderDate=date;
}
CustomerOrder::CustomerOrder(const CustomerOrder& other){
    this->id=other.id;
    this->orderDate=other.orderDate;
    this->customerID=other.customerID;
}
CustomerOrder::~CustomerOrder(){}
void CustomerOrder::readFile(Vector <CustomerOrder>& v){
    ifstream file("order.txt");
    string sv;
    int i;
    CustomerOrder c;
    while (getline(file,sv)){
        if (sv=="") continue;
        i=0;
        CustomerOrder c;
        stringstream sub(sv);
        string s;
        while (getline(sub,s,',')){
            if (s=="") continue;
            if (i==0) c.id=stoi(s);
            else if(i==1) c.customerID=stoi(s);
            else if(i==2) c.orderDate=s;
            else if(i==3) c.sum=stoi(s);
            else {
                size_t p1=s.find(";");
                string id_product=s.substr(1,p1-1);
                int sl=stoi(s.substr(p1+1,s.length()-1-p1));
                c.productList.push_back(id_product,sl);
            }
            i++;
        }
        v.push_back(c);
    }
}
void CustomerOrder::saveFile(const Vector<CustomerOrder> &v) const{
    ofstream file("order.txt");
    for (int i=0;i<v.getsize();i++){
        file<<v[i].id<<","<<v[i].customerID<<","<<v[i].orderDate<<","<<v[i].sum;
        for (int j=0;j<v[i].productList.Get_Size();j++){
            file<<",("<<v[i].productList.getKey(j)<<";"<<v[i].productList.getValue(j)<<")";
        }
        file<<"\n";
    }
}
void CustomerOrder::Create_Order(const Vector <Product> &p ,Vector <CustomerOrder>&v){
    CustomerOrder newOrder;
    newOrder.id=v.getsize();
    newOrder.customerID=current_User.GetID();
    string date;
    cout<<"Nhap ngay thang nam(dd/mm/yyyy):";getline(cin,date);
    newOrder.orderDate=date;
    ds:
    cout<<"Nhap tung dong theo dinh dang: <STT> <SoLuong>. Nhap 0 de ket thuc.\n";
    cout<<"+--------------------------------+--------------------+\n";
    cout<<"| STT san pham (0 = ket thuc)   | So luong           |\n";
    cout<<"+--------------------------------+--------------------+\n";

    string row;
    while (true){
        cout<<"| ";
        getline(cin,row);
        if (row=="") continue;
        if (row=="0") break;
        stringstream ss(row);
        int stt,slg;
        if (!(ss>>stt)){
            cout<<"[Thong bao] Du lieu khong hop le. Vui long nhap lai.\n";
            continue;
        }
        if (stt==0) break;
        if (stt<1 || stt>p.getsize()){
            cout<<"[Thong bao] STT khong ton tai.\n";
            continue;
        }
        if (!(ss>>slg)){
            cout<<"[Thong bao] Vui long nhap so luong sau STT.\n";
            continue;
        }
        Product pr =p[stt-1];
        int slg_max=a.Get_Quantity(pr.Get_ID());
        if (slg<=0 || slg>slg_max){
            cout<<"[Thong bao] So luong hop le tu 1 den "<<slg_max<<".\n";
            continue;
        }
        this->sum+=pr.Get_price()*slg;
        newOrder.productList.push_back(pr.Get_ID(),slg);

        cout<<"\nDanh sach san pham da chon:\n";
        cout<<"+--------------------------------+--------------------+\n";
        cout<<"| Ma san pham                   | So luong           |\n";
        cout<<"+--------------------------------+--------------------+\n";
        for (int idx=0; idx<newOrder.productList.Get_Size(); idx++){
            cout<<"| "<<left<<setw(30)<<newOrder.productList.getKey(idx)
                <<"| "<<setw(18)<<newOrder.productList.getValue(idx)<<"|\n";
        }
        cout<<"+--------------------------------+--------------------+\n";
        cout<<right;
    }
    if (newOrder.productList.Get_Size()==0){
        cout <<"Chua co san pham nao duoc tao. Tro ve menu chinh? (Y/N): ";
        char choice;
        cin>>choice;cin.ignore();
        choice=toupper(choice);
        if (choice=='N') goto ds;
        else {
            User tmp_u;
            tmp_u.user_menu();
        }
    }
    char c;
    cout<<"Xac nhan thanh toan? (Y/N): ";cin>>c;cin.ignore();c=toupper(c);
    if (c=='Y'){    
        for (int i=0;i<newOrder.productList.Get_Size();i++){
            string s=newOrder.productList.getKey(i);
            int slg=newOrder.productList.getValue(i);
            Product tmp,p=tmp.Find_byid(s,Product_List);
            p.Add_sold(slg);
            a.Remove_Product(s,slg);
        }
        v.push_back(newOrder);
        cout<<"Da tao don hang thanh cong\n";
    }else{
        cout<<"Tro ve menu\n";
        User u;
        u.user_menu();
        return;
    }
    return;
}
void CustomerOrder::order_by(const User& cur, const Vector <CustomerOrder>& v,Vector <CustomerOrder>&result){
    for (int i=0;i<v.getsize();i++){
        if (v[i].customerID==cur.GetID()) result.push_back(v[i]);
    }
    return;
}
void CustomerOrder::show() const {
    clear_screen();
    cout << "\n===== HOA DON #" << this->id << " =====\n";
    cout << "Ngay lap: " << this->orderDate << endl;

    if (this->productList.Get_Size() == 0) {
        cout << "[Thong bao] Don hang khong co san pham.\n";
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
    for (int i = 0; i < this->productList.Get_Size(); i++) {
        string idproduct = this->productList.getKey(i);
        int quantity = this->productList.getValue(i);

        string productName = "[Khong tim thay]";
        int unitPrice = 0;

        Product finder;
        try {
            Product p = finder.Find_byid(idproduct, Product_List);
            productName = p.Get_Name();
            unitPrice = p.Get_price();
        }
        catch (const runtime_error&) {
            // Keep default values but note missing product
            productName += " (ID: " + idproduct + ")";
        }

        long long lineTotal = static_cast<long long>(unitPrice) * quantity;
        calculated += lineTotal;

        cout << left
             << setw(5) << i + 1
             << setw(12) << idproduct
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

void CustomerOrder::order_date(const Vector<CustomerOrder>& v,Vector<CustomerOrder>&r,const string&date) const{
    for (int i=0;i<v.getsize();i++)
        if (v[i].orderDate==date) r.push_back(v[i]);
    return;
}
int CustomerOrder::getsum() const{
    return this->sum;
}
