#include <iostream>
#include "myVector.hpp"
#include "model.hpp"
using namespace std;

template <typename T>
myVector<T>::myVector(){
    arr = new T[1];
    capacity = 1;
    current = 0;
}

template <typename T>
void myVector<T>::push(T* data){
    if (current == capacity) {
        T* temp = new T[2 * capacity];

        for (int i = 0; i < capacity; i++) {
            temp[i] = arr[i];
        }

        delete[] arr;
        capacity *= 2;
        arr = temp;
    }

    arr[current] = *data;
    current++;
}

template <typename T>
void myVector<T>::push(T* data, int index)
{
    if (index == capacity)
        push(data);
    else
        arr[index] = *data;
}

template <typename T>
T* myVector<T>::get(int index)
{
    if(index < 0 || index > current) return nullptr;
    return &arr[index];
}

template <typename T>
void myVector<T>::remove(string id) {
    int index = current;
    for (int i = 0; i < current; i++){
        if(arr[i].getId().compare(id) == 0){
            index = i;
            break;
        }
    }

    for (int i = index; i < current - 1; i++) {
        arr[i] = arr[i + 1];
    }
    if(index <= current) current--;
}

template <>
void myVector<string>::remove(string id) {
    int index = current;
    for (int i = 0; i < current; i++){
        if(arr[i].compare(id) == 0){
            index = i;
            break;
        }
    }

    for (int i = index; i < current - 1; i++) {
        arr[i] = arr[i + 1];
    }
    if(index <= current) current--;
}

template <>
void myVector<myVector<string>>::remove(string id){}

template <typename T>
int myVector<T>::size() {
    return current;
}

template <typename T>
T* myVector<T>::search(string id) {
    for(int i = 0; i < current; i++){
        if(arr[i].getId() == id){
            return &arr[i];
        }
    }
    return nullptr;
}

template <>
string* myVector<string>::search(string id) {
    for(int i = 0; i < current; i++){
        if(arr[i] == id)
            return &arr[i];
    }
    return nullptr;
}

template <>
myVector<string>* myVector<myVector<string>>::search(string id) {
    return nullptr;
}

template <typename T>
void myVector<T>::clear(){
    delete []arr;
}

template class myVector<dosen>;
template class myVector<matkul>;
template class myVector<mahasiswa>;
template class myVector<transkrip>;
template class myVector<string>;
template class myVector<myVector<string>>;