
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>

#include "model.hpp"
#include "myVector.hpp"
#include "hashmap.hpp"

using namespace std;

void banner(){
    cout << " ======================================================== " << endl;
    cout << "  __          ________ _      _____ ____  __  __ ______ " << endl;
    cout << "  \\ \\        / /  ____| |    / ____/ __ \\|  \\/  |  ____|" << endl;
    cout << "   \\ \\  /\\  / /| |__  | |   | |   | |  | | \\  / | |__   " << endl;
    cout << "    \\ \\/  \\/ / |  __| | |   | |   | |  | | |\\/| |  __|  " << endl;
    cout << "     \\  /\\  /  | |____| |___| |___| |__| | |  | | |____ " << endl;
    cout << "      \\/  \\/   |______|______\\_____\\____/|_|  |_|______|" << endl;
    cout << " ======================================================== " << endl;
    cout << " Student Management System " << endl;
}


void option(){
    cout << endl;
    cout << "1. Masukkan Data Mahasiswa" << endl;
    cout << "2. Telusuri Data Mahasiswa" << endl;
    cout << "3. Tampilkan Semua" << endl;
    cout << "4. Kembali" << endl;
    cout << "Masukkan input anda: " << endl;
}

bool isLen(string line){
    if(line.length() > 4){
        return true;
    }
    return false;
}

bool isNum(string line){
    for( int i = 0; i < line.length(); i++ ) {
        if( !isdigit( line[i] )) {
            return false;
        }
    }
    return true;
}

bool isId(string line){
    if(isupper(line[0]) != 0 && isNum(line.substr(1,line.length()-1))){
        return true;
    }
    return false;
}

myVector<myVector<string>> *readFile(char* fname){
    ifstream file(fname);
    string line;
    myVector<myVector<string>> *table = new myVector<myVector<string>>();

    while (getline(file, line)) {
        myVector<string> *row = new myVector<string>();
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ';')) {
            row->push(&cell);
        }
        table->push(row);
    }

    return table;
}
                                             
int main(){
    banner();
    hashmap *mhs = new hashmap();
    myVector<dosen> *lec = new myVector<dosen>();
    
    // baca dari database dosen
    string file = "database/dosen.csv";
    myVector<myVector<string>>* table = readFile(&file[0]);
    for(int i = 0; i < table->size(); i++){
        dosen *temp = new dosen(*table->get(i)->get(0), *table->get(i)->get(1), (*table->get(i)->get(2))[0]);
        lec->push(temp);
    }

    // baca dari database mahasiswa
    file = "database/mahasiswa.csv";
    table = readFile(&file[0]);
    for(int i = 0; i < table->size(); i++){
        dosen* dosbing = lec->search(*table->get(i)->get(3));
        mahasiswa *temp = new mahasiswa(*table->get(i)->get(0), *table->get(i)->get(1), (*table->get(i)->get(2))[0], dosbing);
        mhs->insertElem(*temp);
    }

    string input;
    while(true){
        option();
        cout << ">> ";
        cin >> input;
        if(input == "1"){
            cout << "INPUT DATA MAHASISWA" << endl;
            cout << "====================" << endl;
            string name, nim;
            char gender;
            int dosbing, krs;

            while(true){
                cout << "Masukkan Nama: ";
                char ch;
                cin >> ch;
                getline(cin, name);
                if(!isLen(name)) cout << endl << "Input nama minimal mengandung 3 karakter!" << endl << endl;
                else if(name.length() > 255){
                    name = name.substr(0, 255);
                    cout << endl << "Input maksimal 255 karakter!" << endl << endl;
                    break;
                }else{
                    cout << endl;
                    break;
                }
            }
            
            while(true){
                cout << "Masukkan NIM: ";
                getline(cin, nim);
                if(!isLen(nim)) cout << endl << "Input nama minimal mengandung 3 karakter!" << endl << endl;
                else if(!isId(nim)) cout << endl << "Input harus merupakan format nim (ex: X0123456)!" << endl << endl;
                else if(mhs->searchElem(nim)) cout << endl << "NIM sudah pernah digunakan!" << endl << endl;
                else if(nim.length() > 255){
                    nim = nim.substr(0, 255);
                    cout << endl << "Input maksimal 255 karakter!" << endl << endl;
                    break;
                }else{
                    cout << endl;
                    break;
                }
            }

            while(true){
                int temp;
                cout << "Pilih Jenis Kelamin:" << endl; 
                cout << "1. Laki-laki \t2. Perempuan" << endl;
                cout << ">> ";
                cin >> temp;
                if(temp != 1 && temp != 2) cout << endl << "Input tidak valid!" << endl << endl ;
                else{
                    if(temp == 1) gender = 'L';
                    else gender = 'P';
                    cout << endl;
                    break;
                }
            }

            while(true){
                int qt = lec->size();
                cout << "Pilih Dosen Pembimbing:" << endl;
                for(int i = 0; i < qt; i++){
                    cout << i+1 << ". " << lec->get(i)->getNama() << " (" << lec->get(i)->getId() << ")" << endl;
                }
                cout << "0. Belum memiliki Dosen Pembimbing" << endl;
                cout << ">> ";
                cin >> dosbing;
                if(dosbing >= 0 && dosbing <= qt){
                    cout << endl;
                    break;
                } else cout << endl << "Input tidak valid!" << endl << endl ;
            }

            mahasiswa *val = new mahasiswa(name, nim, gender, lec->get(dosbing-1));
            mhs->insertElem(*val);
            cout << "Berhasil Menambahkan Data Mahasiswa!" << endl;
        }
        else if(input == "2"){
            while(true){
                string search;
                Node<mahasiswa>* node;
                cout << "Masukkan NIM yang ingin dicari: " << endl;
                cin >> search;
                if(search == "q"){
                    break;
                }else if(node = mhs->searchElem(search)){
                    mahasiswa data = node->data;
                    int opt;
                    do{
                        cout << endl << "[[ " << data.getNama() << " | " << data.getId() << " ]]" << endl << endl;
                        cout << "1. Edit" << endl;
                        cout << "2. Delete" << endl;
                        cout << "3. Print" << endl;
                        cout << "0. Kembali" << endl;
                        cout << ">> ";
                        cin >> opt;
                        if(opt == 1){
                            
                        }else if(opt == 2){
                            mhs->deleteElem(node);
                            cout << endl << "Data Mahasiswa berhasil dihapus!" << endl;
                        }else if(opt == 3){
                            
                            cout << "" << endl;
                        }else if(opt != 0){
                            cout << "Input tidak valid!" << endl;
                        }
                    } while(opt != 0 && opt != 2 && opt != 3);
                }else{
                    cout << "Mahasiswa tidak ditemukan" << endl;
                }
                cout << "~~ tekan \"q\" untuk kembali ke menu utama! ~~" << endl;
            }
        }
        else if(input == "3"){
            cout << "TAMPILIN JUMLAH MAHASISWA" << endl;
            cout << "TAMPILIN SEMUA table MAHASISWA (SORTED by NIM)" << endl;
        }
        else if(input == "4"){
            system("cls");
            cout << "Bye!\n" << endl;
            break;
        }else if(input == "cls" || input == "clear"){
            system("cls");
        }else{
            cout << "Input tidak valid" << endl << endl;
        }
    }
    
    return 0;
}