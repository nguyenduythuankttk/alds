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
    string s;
    int i;
    CustomerOrder c;
    while (getline(file,s)){
        if (s=="") continue;
        i=0;
        stringstream sub(s);
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
    cout<<"Nhap ngay thang nam(dd/mm/yyyy)";cin>>date;
    newOrder.orderDate=date;
    ds:
    cout<<"Nhap danh sach san pham va so luong muon mua";
    cout<<"Nhap 0 de ket thuc";
    int stt,slg,slg_max;
    do{
        cout<<"Nhap so thu tu san pham:";cin>>stt;
        if (stt==0) break;
        Product pr =p[stt-1];
        slg_max=a.Get_Quantity(pr.Get_ID());
        cout<<pr.Get_Name()<<pr.Get_price()<<slg_max;
        do {
        cout<<"Nhap so luong san pham can mua:"; 
        cin>>slg;
        }while (slg>slg_max && slg<0);
        newOrder.productList.push_back(pr.Get_ID(),slg);
    }while (stt!=0);
    if (newOrder.productList.Get_Size()==0){
        cout <<"Chua co san pham nao duoc tao.Tro ve menu chinh?(Y/N)";
        char choice;
        cin>>choice;
        choice=toupper(choice);
        if (choice=='N') goto ds;
       // else //;
    }
    v.push_back(newOrder);
    cout<<"Da tao don hang thanh cong\n";
    return;
}