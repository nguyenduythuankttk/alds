#pragma once
#include <iostream>
using namespace std;
template <typename T>
class Vector{
    private:
        int capacity;
        int cur;
        T *arr;
    public:
        Vector(const int& =100);
        ~Vector();
        void push_back(const T&);
        T& operator[](const int&) const;
        //T& operator=(const T&);
        void Erase();
        int getsize() const;
        //const T& operator[](int index) const;
};
template <typename T>
Vector<T>::Vector(const int& capacity):capacity(capacity){
    this->arr=new T[capacity];
    this->cur=0;
}
template <typename T>
Vector<T>::~Vector(){
    delete[] this->arr;
}
template <typename T>
void Vector<T>::push_back(const T& x){
    *(this->arr+this->cur) =x;
    this->cur++;
    if (this->cur==this->capacity){
        T *temp =new T[this->capacity];
        for (int i=0;i<this->capacity;i++)
            *(temp+i)=*(this->arr+i);
        delete [] this->arr;
        this->arr=new T[this->capacity*2];
        this->capacity*=2;
        for (int i=0;i<this->capacity;i++)
            *(this->arr+i)=*(temp+i);
        delete [] temp;
    }
}
template <typename T>
T& Vector<T>::operator[](const int& i) const{
    if (i>=0 && i<this->cur) return *(this->arr+i);
    else {cout<<"out range";
        return *(this->arr);
    }
}
template <typename T>
void Vector<T>::Erase(){
    delete this->arr;
    this->cur=0;
    this->arr=new T[this->capacity];
} 
template <typename T>
int Vector<T>::getsize() const{
    return this->cur;
}