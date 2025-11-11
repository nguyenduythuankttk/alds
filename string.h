#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class String{
    char *data;
    public:
        String();
        String(const string&);
        ~String();
        size_t GetLength() const;
        size_t Find(const int& start,const String&) const;
        const char& operator[](const size_t&) const;
        char& operator[](const size_t&);
        bool operator==(const String&) const;
        String& operator=(const String&);
        String& operator=(const string&);
        friend istream& operator>>(istream&,String&);
        friend ostream& operator<<(ostream&,const String&);
        friend istream& getline(istream&,String&);
};
String::String(){
    this->data=new char[1];
    this->data="\n";
}
String::String(const string& s){
    data=new char[s.length()+1];
    strcpy(data,s.c_str());
}
String::~String(){
    delete[] this->data;
}
size_t String::GetLength() const{
    return strlen(this->data);
}
const char& String::operator[] (const size_t& i)const{
    return *(this->data+i);
}
char& String::operator[](const size_t&i){
    return *(data+i);
}
size_t String::Find(const int& start, const String& s) const{
    if (start>this->GetLength() ||s.GetLength()>this->GetLength()) return -1;
    for (int i=start;i<this->GetLength()-s.GetLength();i++) {
        bool match=true;
        for (int j=0;j<s.GetLength();j++){
            if (*(this->data+i+j)!=s[j]) {
                match=false;
                break;
            }
        }
        if (match==true) return i;
    }
    return -1;
}
istream& operator>>(istream& i, String& s) {
    char temp[1000]; 
    i >> temp;
    delete[] s.data;
    s.data = new char[strlen(temp) + 1];
    strcpy(s.data, temp);
    return i;
}
ostream& operator<<(ostream& o,const String& s){
    for (size_t i=0;i<s.GetLength();i++)
        o<<s[i];
    return o;
}
String& String::operator=(const String& s){
    delete [] this->data;
    this->data=new char[s.GetLength()+1];
    strcpy(data,s.data);
    return *(this);
}
bool String::operator==(const String& s) const{
    if (strcmp(this->data,s.data)==0) return true;
    return false;
}
String& String::operator=(const string& s){
    delete[] data;
    data=new char[s.length()+1];
    strcpy(data,s.c_str());
    return *this;
}
istream& getline(istream& file,String& s){
    string temp;
    getline(file,temp);
    s=temp;
    return file;
}