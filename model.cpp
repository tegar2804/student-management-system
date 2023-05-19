#include "model.hpp"
using namespace std;

student::student(){
    nama = id = "";
    gender = ' ';
    ip = 0;
}

void student::set(string name, string nim, char jk, double nilai){
    nama = name;
    id = id;
    gender = jk;
}

string student::getId(){
    return id;
}