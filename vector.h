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
        Vector(const Vector<T>&); 
        Vector<T>& operator=(const Vector<T>&);
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
Vector<T>::Vector(const Vector<T>& other) {
    capacity = other.capacity;
    cur = other.cur;
    arr = new T[capacity];
    for (int i = 0; i < cur; i++) arr[i] = other.arr[i];
}
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this == &other) return *this;
    delete[] arr;
    capacity = other.capacity;
    cur = other.cur;
    arr = new T[capacity];
    for (int i = 0; i < cur; i++) arr[i] = other.arr[i];
    return *this;
}
template <typename T>
Vector<T>::~Vector(){
    delete[] this->arr;
}
template <typename T>
void Vector<T>::push_back(const T& x) {
    if (cur == capacity) {
        capacity *= 2;
        T* temp = new T[capacity];
        for (int i = 0; i < cur; i++) temp[i] = arr[i];
        delete[] arr;
        arr = temp;
    }
    arr[cur++] = x;
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
    delete []this->arr;
    this->cur=0;
    this->arr=new T[this->capacity];
} 
template <typename T>
int Vector<T>::getsize() const{
    return this->cur;
}