#include <iostream>
#include <string>
#include <sstream>
using namespace std;
int main(){
    string s="1,2,dfs,56,7,(32;4),(ads;3)\n";
        stringstream sub(s);
        int i=0;
        string date;
        int id,employeeID,sum,warehouseID;
        while (getline(sub,s,',')){
            if (s=="") continue;
            if (i==0) id=stoi(s);
            else if(i==1) employeeID=stoi(s);
            else if(i==2) date=s;
            else if(i==3) sum=stoi(s);
            else if (i==4) warehouseID=stoi(s);
            else {
                size_t p1=s.find(";");
                string id_product=s.substr(1,p1-1);
                int sl=stoi(s.substr(p1+1,s.length()-1-p1));
                //p.List.push_back(id_product,sl);
                cout<<id_product<<sl<<"\n";
            }
            i++;
        }

}