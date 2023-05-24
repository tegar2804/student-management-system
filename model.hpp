#pragma once

#include <iostream>
#include "myVector.hpp"

class dosen
{
    private:
        std::string nama, id;
        char gender;
    public:
        dosen();
        dosen(std::string, std::string, char);
        std::string getId();
        std::string getNama();
        char getJk();
};

class matkul
{
    private:
        std::string nama, id;
        int sks;
    public:
        matkul();
        matkul(std::string, std::string, int);
        std::string getId();
        std::string getNama();
        int getSKS();
};

class transkrip
{
    private:
        std::string id;
        matkul *kode;
        std::string mutu;
    public:
        transkrip();
        transkrip(std::string, matkul*, std::string);
        matkul* getMatkul();
        std::string getId();
        double getMutuDouble();
        std::string getMutuChar();
};

class mahasiswa
{
    private:
        std::string nama, id;
        char gender;
        double ip;
        dosen* dosbing;
        myVector<transkrip>* krs;
    public:
        mahasiswa();
        mahasiswa(std::string, std::string, char, dosen*, myVector<transkrip>*);
        void recount_IP();
        void setNama(std::string);
        void setId(std::string);
        void setGender(char);
        void setDosbing(dosen*);
        std::string getId();
        std::string getNama();
        void addKRS(transkrip*);
        void deleteKRS(std::string);
        char getJk();
        double getIP();
        dosen* getDosbing();
        myVector<transkrip>* getKRS();
};