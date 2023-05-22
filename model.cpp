#include "model.hpp"
using namespace std;

dosen::dosen(){
    nama = id = "";
    gender = ' ';
}

dosen::dosen(string name, string nrp, char jk){
    nama = name;
    id = nrp;
    gender = jk;
}

string dosen::getId(){
    return id;
}

string dosen::getNama(){
    return nama;
}


mahasiswa::mahasiswa(){
    nama = "";
    id = "0";
    gender = ' ';
    ip = 0;
}

mahasiswa::mahasiswa(string name, string nim, char jk, dosen lec){
    nama = name;
    id = nim;
    gender = jk;
    dosbing = &lec;
}

string mahasiswa::getId(){
    return id;
}

void mahasiswa::setNama(string name){
    nama = name;
}

void mahasiswa::setId(string nim){
    id = nim;
}

void mahasiswa::setGender(char jk){
    gender = jk;
}

void mahasiswa::setDosbing(dosen lec){
    dosbing = &lec;
}