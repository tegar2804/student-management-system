#pragma once

#include <iostream>

class student
{
    private:
        std::string nama, id;
        char gender;
        double ip;
    public:
        student();
        void set(std::string, std::string, char, double);
        std::string getId();
};

class transkrip
{
    private:
        std::string nim, kode;
    public:
        transkrip(){
            nim = kode = "";
        }
        void set(std::string nrp, std::string id){
            nim = nrp;
            kode = id;
        }
};

class matkul
{
    private:
        std::string nama, kode;
    public:
        matkul(){
            nama = kode = "";
        }
        void set(std::string name, std::string id){
            nama = name;
            kode = id;
        }
};