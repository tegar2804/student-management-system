
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
#include "vector.hpp"
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
    cout << "1. Masukkan table Mahasiswa" << endl;
    cout << "2. Cari table Mahasiswa" << endl;
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
    if(isupper(line[0]) == 1 && isNum(line.substr(1,line.length()-1)) == 1){
        return true;
    }
    return false;
}

vector<vector<string>> *readFile(char* fname){
    ifstream file(fname);
    string line;
    vector<vector<string>> *table = new vector<vector<string>>();

    while (getline(file, line)) {
        vector<string> *row = new vector<string>();
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ';')) {
            row->push(cell);
        }
        table->push(*row);
    }

    return table;
}
                                             
int main(){
    banner();
    hashmap *mhs = new hashmap();
    vector<dosen> *lec = new vector<dosen>();
    string input;
    string file = "database/mahasiswa.csv";
    vector<vector<string>>* table_mhs = readFile(&file[0]);
    for(int i = 0; i < table_mhs->size(); i++){
        for(int j = 0; j < table_mhs->get(i).size(); j++){
            cout << table_mhs->get(i).get(j) << " ";
        }
        cout << endl;
    }
    while(true){
        option();
        cout << ">> ";
        cin >> input;
        if(input == "1"){
            cout << "INPUT table" << endl;
            cout << "===============" << endl;
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
                }else break;
            }
            
            while(true){
                cout << "Masukkan NIM: ";
                getline(cin, nim);
                if(!isLen(nim)) cout << endl << "Input nama minimal mengandung 3 karakter!" << endl << endl;
                else if(!isId(nim)) cout << endl << "Input harus merupakan format nim (ex: X0123456)!" << endl << endl;
                else if(nim.length() > 255){
                    nim = nim.substr(0, 255);
                    cout << endl << "Input maksimal 255 karakter!" << endl << endl;
                    break;
                }else break;
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
                    break;
                }
            }

            while(true){
                int qt = lec->size();
                cout << "Pilih Dosen Pembimbing:" << endl;
                for(int i = 0; i < qt; i++){
                    cout << i+1 << ". " << lec->get(i).getNama() << endl;
                }
                cout << ">> ";
                cin >> dosbing;
                if(dosbing >= 1 && dosbing <= qt) break;
                else cout << endl << "Input tidak valid!" << endl << endl ;
            }

            mahasiswa *val = new mahasiswa(name, nim, gender, lec->get(dosbing-1));
            mhs->insertElem(*val);
            cout << "Berhasil Menambahkan table Mahasiswa!" << endl;
        }
        else if(input == "2"){
            while(true){
                string search;
                cout << "masukkan NIM yang ingin dicari: " << endl;
                cin >> search;
                if(search == "q"){
                    break;
                // fungsi cari blom dibuat
                }else if(true){
                    cout << "1. Edit" << endl;
                    cout << "2. Delete" << endl;
                    cout << "3. Print" << endl;
                    cout << "0. Kembali" << endl;
                }else{
                    cout << "Mahasiswa tidak ditemukan" << endl;
                }
                cout << "tekan \"q\" untuk kembali ke menu!" << endl;
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