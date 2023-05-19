#pragma once

#include <iostream>

template <typename T>
class vectorClass{
    private:
        T* arr;
        int capacity;
        int current;
    public:
        vectorClass();
        ~vectorClass();
        void push(T);
        void push(T, int);
        T get(int);
        void pop();
        int size();
        int getcapacity();
        void print();
};