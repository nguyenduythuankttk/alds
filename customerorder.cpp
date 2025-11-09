#include "customerorder.h"
#include <fstream>
#include <sstream>
#include "global.cpp"
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