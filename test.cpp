#include "map.h"
int main(){
    Map<string,int> pr;
    pr.push_back("aa",100);
    pr.push_back("ajfd",3);
    cout<<pr.Find_key("aa");
    cout<<pr.Get_Size();
}