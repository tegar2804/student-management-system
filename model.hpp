#pragma once

#include <iostream>

class dosen
{
    private:
        std::string nama, id;
        char gender;
        double ip;
    public:
        // dosen();
        // dosen(std::string, std::string, char);
        // void setNama(std::string);
        // void setId(std::string);
        // void setGender(char);
        // void setDosbing(int);
        // std::string getId();
};

class mahasiswa
{
    private:
        std::string nama, id;
        char gender;
        double ip;
        dosen dosbing;
    public:
        mahasiswa();
        mahasiswa(std::string, std::string, char);
        void setNama(std::string);
        void setId(std::string);
        void setGender(char);
        void setDosbing(int);
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