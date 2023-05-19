#pragma once

#include <iostream>

class Mahasiswa{
    private:
    std::string nama;
    std::string nim;
    public:
    Mahasiswa(){
        nama="";
        nim="";
    }
    Mahasiswa(std::string name, std::string id){
        nama=name;
        nim=id;
    }
    std::string getNama(){
        return nama;
    }
    std::string getNim(){
        return nim;
    }
    void input(std::string name, std::string id){
        nama=name;
        nim=id;
    }
    void editNama(std::string name){
        nama=name;
    }
    void editNim(double id){
        nim=id;
    }
};

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