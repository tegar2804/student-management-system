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

char dosen::getJk(){
    return gender;
}

matkul::matkul(){
    nama = id = "";
    sks = 0;
}

matkul::matkul(string name, string kode, int s){
    nama = name;
    id = kode;
    sks = s;
}

string matkul::getId(){
    return id;
}

string matkul::getNama(){
    return nama;
}

int matkul::getSKS(){
    return sks;
}

transkrip::transkrip(){
    id = "";
    kode = nullptr;
    mutu = "BL";
}

transkrip::transkrip(string nrp, matkul *code, string m){
    id = nrp;
    kode = code;
    mutu = m;
}

matkul* transkrip::getMatkul(){
    return kode;
}

string transkrip::getId(){
    return getMatkul()->getId();
}

double transkrip::getMutuDouble(){
    if(mutu == "A") return 4;
    else if(mutu == "AB") return 3.5;
    else if(mutu == "B") return 3;
    else if(mutu == "BC") return 2.5;
    else if(mutu == "C") return 2;
    else if(mutu == "D") return 1;
    else return 0;
}

string transkrip::getMutuChar(){
    return mutu;
}

void mahasiswa::recount_IP(){
    double ans = 0;
    int sum = 0;
    for(int i = 0; i < krs->size(); i++){
        ans += krs->get(i)->getMutuDouble() * (double)krs->get(i)->getMatkul()->getSKS();
        if(krs->get(i)->getMutuDouble() > 0)
            sum += krs->get(i)->getMatkul()->getSKS();
    }
    if(sum > 0) ip = ans / (1.0*sum);
    else ip = 0;
}

mahasiswa::mahasiswa(){
    nama = "";
    id = "0";
    gender = ' ';
    ip = 0;
    krs = new myVector<transkrip>();
}

mahasiswa::mahasiswa(string name, string nim, char jk, dosen* lec, myVector<transkrip>* list_krs){
    nama = name;
    id = nim;
    gender = jk;
    dosbing = lec;
    ip = 0;
    krs = list_krs;
    this->recount_IP();
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

void mahasiswa::setDosbing(dosen* lec){
    dosbing = lec;
}


string mahasiswa::getId(){
    return id;
}

string mahasiswa::getNama(){
    return nama;
}

char mahasiswa::getJk(){
    return gender;
}

double mahasiswa::getIP(){
    return ip;
}

dosen* mahasiswa::getDosbing(){
    return dosbing;
}

myVector<transkrip>* mahasiswa::getKRS(){
    return krs;
}

void mahasiswa::addKRS(transkrip* tran){
    krs->push(tran);
    this->recount_IP();
}

void mahasiswa::deleteKRS(string code){
    krs->remove(code);
    this->recount_IP();
}
