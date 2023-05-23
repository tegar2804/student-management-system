#pragma once

#include <iostream>

template <typename T>
class myVector{
    private:
        T* arr;
        int capacity;
        int current;
    public:
        myVector();
        void push(T*);
        void push(T*, int);
        T* get(int);
        void pop(int);
        int size();
        T* search(std::string);
        void clear();
};