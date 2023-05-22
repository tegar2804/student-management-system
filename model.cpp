#include "model.hpp"
using namespace std;

mahasiswa::mahasiswa(){
    nama = "";
    id = "0";
    gender = ' ';
    ip = 0;
}

mahasiswa::mahasiswa(string name, string nim, char jk){
    nama = name;
    id = nim;
    gender = jk;
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