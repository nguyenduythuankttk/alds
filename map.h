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
        Map(const Map<T,U>&);
        Map<T,U>& operator=(const Map<T,U>&);
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
template <typename T, typename U>
Map<T,U>::Map(const Map<T,U>& other) {
    capacity = other.capacity;
    cur = other.cur;
    key = new T[capacity];
    data = new U[capacity];
    for (int i = 0; i < cur; i++) {
        key[i] = other.key[i];
        data[i] = other.data[i];
    }
}
template <typename T, typename U>
Map<T,U>& Map<T,U>::operator=(const Map<T,U>& other) {
    if (this == &other) return *this;
    delete[] key;
    delete[] data;
    capacity = other.capacity;
    cur = other.cur;
    key = new T[capacity];
    data = new U[capacity];
    for (int i = 0; i < cur; i++) {
        key[i] = other.key[i];
        data[i] = other.data[i];
    }
    return *this;
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
template <typename T, typename U>
void Map<T,U>::push_back(const T& k, const U& v) {
    if (cur == capacity) {
        capacity *= 2;
        T* newKey = new T[capacity];
        U* newdata = new U[capacity];
        for (int i = 0; i < cur; i++) {
            newKey[i] = key[i];
            newdata[i] = data[i];
        }
        delete[] key;
        delete[] data;
        key = newKey;
        data = newdata;
    }
    key[cur] = k;
    data[cur] = v;
    cur++;
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