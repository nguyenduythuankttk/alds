#include "library.h"
using namespace std;
void readfile(ifstream &filename,Vector<User> &v){
    string s;
    int i;
    User u;
    //ifstream filename("user.txt");
    while (getline(filename,s)){
        if (s=="") continue;
        i=0;
        stringstream sub(s);
        while (getline(sub,s,',')){
            if (i==0) u.SetuserID(stoi(s));
            else if(i==1) u.Setusername(s);
            else u.Setpassword(s);
            i++;
        }
        v.push_back(u);
    }
}

int main(){
    Vector <User> u;
    ifstream file("user.txt");
    readfile(file,u);
    for (int i=0;i<u.getsize();i++)
        u[i].ShowInfo();
    return 0;
}