#include "customerorder.h"
#include "library.h"        
#include "warehouse.h"       
#include "product.h"         
#include "user.h"       
#include <fstream>
#include <sstream>
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
    cout<<"Nhap danh sach san pham va so luong muon mua\n";
    cout<<"Nhap 0 de ket thuc\n";

    int stt,slg,slg_max;
    do{
        cout<<"Nhap so thu tu san pham: ";cin>>stt;cin.ignore();
        if (stt==0) break;
        Product pr =p[stt-1];
        slg_max=a.Get_Quantity(pr.Get_ID());
        cout<<"Ten san pham: "<<pr.Get_Name()<<"Gia: "<<pr.Get_price()<<"So luong: "<<slg_max<<endl;
        do {
        cout<<"Nhap so luong san pham can mua: "; 
        cin>>slg;cin.ignore();
        this->sum+=pr.Get_price()*slg;
        }while (slg>slg_max && slg<0);
        newOrder.productList.push_back(pr.Get_ID(),slg);
    }while (stt!=0);
    if (newOrder.productList.Get_Size()==0){
        cout <<"Chua co san pham nao duoc tao.Tro ve menu chinh?(Y/N)";
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
    cout<<"Xac nhan thanh toan?(Y/N)";cin>>c;cin.ignore();c=toupper(c);
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
    cout << "Hoa don:\n" << this->orderDate << endl;
    for (int i = 0; i < this->productList.Get_Size(); i++) {
        string idproduct = this->productList.getKey(i);
        int quantity = this->productList.getValue(i);

        Product tmp;
        try {
            Product p = tmp.Find_byid(idproduct, Product_List);
            cout << "Ten san pham: " << p.Get_Name()
                 << " | So luong: " << quantity
                 << " | Gia: " << p.Get_price() << endl;
        }
        catch (const runtime_error&) {
            cout << "[Canh bao] San pham ID=" << idproduct
                 << " khong ton tai trong danh sach san pham."
                 << " | So luong: " << quantity << endl;
        }
    }
    cout << "Tong tien: " << this->sum << endl;
}

void CustomerOrder::order_date(const Vector<CustomerOrder>& v,Vector<CustomerOrder>&r,const string&date) const{
    for (int i=0;i<v.getsize();i++)
        if (v[i].orderDate==date) r.push_back(v[i]);
    return;
}
int CustomerOrder::getsum() const{
    return this->sum;
}