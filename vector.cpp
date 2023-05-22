#include <iostream>
#include "vector.hpp"
#include "model.hpp"
using namespace std;

template <typename T>
vector<T>::vector(){
    arr = new T[1];
    capacity = 1;
    current = 0;
}

template <typename T>
void vector<T>::push(T data){
    if (current == capacity) {
        T* temp = new T[2 * capacity];

        for (int i = 0; i < capacity; i++) {
            temp[i] = arr[i];
        }

        delete[] arr;
        capacity *= 2;
        arr = temp;
    }

    arr[current] = data;
    current++;
}

template <typename T>
void vector<T>::push(T data, int index)
{
    if (index == capacity)
        push(data);
    else
        arr[index] = data;
}

template <typename T>
T vector<T>::get(int index)
{
    return arr[index];
}

template <typename T>
void vector<T>::pop() { 
    current--; 
}

template <typename T>
int vector<T>::size() {
    return current;
}

template <typename T>
int vector<T>::getcapacity() {
    return capacity;
}

template <typename T>
void vector<T>::clear(){
    delete []arr;
}

template class vector<dosen>;
template class vector<string>;
template class vector<vector<string>>;