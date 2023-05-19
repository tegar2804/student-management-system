#include <iostream>
#include "vector.hpp"
using namespace std;

template <typename T>
vectorClass<T>::vectorClass(){
    arr = new T[1];
    capacity = 1;
    current = 0;
}

template <typename T>
vectorClass<T>::~vectorClass(){
    delete []arr;
}

template <typename T>
void vectorClass<T>::push(T data){
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
void vectorClass<T>::push(T data, int index)
{

    if (index == capacity)
        push(data);
    else
        arr[index] = data;
}

template <typename T>
T vectorClass<T>::get(int index)
{

    if (index < current)
        return arr[index];
}

template <typename T>
void vectorClass<T>::pop() { current--; }

template <typename T>
int vectorClass<T>::size() { return current; }

template <typename T>
int vectorClass<T>::getcapacity() { return capacity; }

template <typename T>
void vectorClass<T>::print()
{
    for (int i = 0; i < current; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}