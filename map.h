#pragma once
#include <iostream>
using namespace std;
template <typename T,typename U>
class Map{
    U* data;
    T *key;
    unsigned int capacity;
    unsigned int cur;
    public:
        Map(const int& =100);
        ~Map();
        int Get_Size() const;
        void push_back(const T&,const U&);
        bool Is_Empty() const;
        U& Find_key(const T&) const;
        T& getKey( int) const;
        U& getValue(int) const;
        void addValue(int,int);
        void removeValue(int,int);
};
template <typename T,typename U>
Map<T,U>::Map(const int& capacity):capacity(capacity){
    this->data=new U[capacity];
    this->key=new T[capacity];
    this->cur=0;
}
template <typename T,typename U>
Map<T,U>::~Map(){
    delete[] this->data;
    delete[] this->key;
}
template <typename T,typename U>
bool Map<T,U>::Is_Empty() const{
    return (this->cur==0);
}
template <typename T,typename U>
int Map<T,U>::Get_Size() const{
    return this->cur;
}
template <typename T,typename U>
U& Map<T,U>::Find_key(const T& Key) const{
    for (int i=0;i<this->Get_Size();i++)
        if (*(this->key+i)==Key) return *(this->data+i);
    cout<<"Not found";
    return *(new U);
}
template <typename T,typename U>
void Map<T,U>::push_back(const T& Key,const U& Data){
    *(this->key+this->cur)=Key;
    *(this->data+this->cur)=Data;
    this->cur++;
    if (this->cur==this->capacity) {
        T *tmp_key=new T[this->capacity];
        U *tmp_data=new U[this->capacity];
        for (int i=0;i<this->capacity;i++){
            *(tmp_key+i)=*(this->key+i);
            *(tmp_data+i)=*(this->data+i);
        }
        delete[] this->data;
        delete[] this->key;
        this->capacity*=2;
        this->data=new U[this->capacity];
        this->key=new T[this->capacity];
        delete[] tmp_key;
        delete[] tmp_data;
    }
}
template <typename T,typename U>
T& Map<T,U>::getKey( int index) const {
    return this->key[index];
}
template <typename T,typename U>
U& Map<T,U>::getValue( int index) const {
    return this->data[index];
}
template <typename T,typename U>
void Map<T,U>::addValue(int index,int value){
    this->data[index]+=value;
}
template <typename T,typename U>
void Map<T,U>::removeValue(int index,int value){
    this->data[index]-=value;
}