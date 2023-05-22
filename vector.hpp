#pragma once

#include <iostream>

template <typename T>
class vector{
    private:
        T* arr;
        int capacity;
        int current;
    public:
        vector();
        void push(T);
        void push(T, int);
        T get(int);
        void pop();
        int size();
        int getcapacity();
        void clear();
};