
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
// #include "node.hpp"
// #include "DLL.hpp"
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
    cout << "2. Cari Data Mahasiswa" << endl;
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
    if(isupper(line[0]) == 1 && isNum(line.substr(line.length()-3,3))){
        return true;
    }
    return false;
}

// void readFile(char* fname){
//     FILE *file = fopen(fname, "r");
 
// 	if(!file)
// 	{
// 		printf("Gagal saat membuka file!\n");
// 		exit(0);
// 	}
 
// 	char content[1024];
// 	while(fgets(content, 1024, file))
// 	{
// 		char *v = strtok(content, ",");
// 		while(v)
// 		{
// 			printf("%s ", v);
// 			v = strtok(NULL, ",");
// 		}
// 		printf("\n");
// 	}
// 	fclose(file);

//     // return content;
// }
                                             
int main(){
    banner();
    hashmap *mhs = new hashmap();
    string input;
    while(true){
        option();
        cout << ">> ";
        cin >> input;
        if(input == "1"){
            cout << "INPUT DATA" << endl;
            cout << "===============" << endl;
            string name, nim;
            char gender;
            int dosbing, krs;
            while(true){
                cout << "masukkan nama: ";
                getline(cin, name);
                if(!isLen(name)) cout << "Input nama minimal mengandung 3 karakter!" << endl << endl;
                else break;
            }
            
            while(true){
                cout << "masukkan NIM: ";
                getline(cin, nim);
                if(!isLen(nim)) cout << "Input nama minimal mengandung 3 karakter!" << endl << endl;
                else if(!isId(nim)) cout << "Input harus merupakan format nim (ex: X0123456)!" << endl << endl;
                else break;
            }

            while(true){
                int temp;
                cout << "pilih gender:" << endl; 
                cout << "1. laki-laki 2. perempuan" << endl;
                cout << ">> ";
                cin >> temp;
                if(temp != 1 && temp != 2) cout << "Input tidak valid!";
                else{
                    if(temp == 1) gender = 'L';
                    else gender = 'P';
                    break;
                }
            }
            
            cout << "pilih dosbing: ..." << endl;
            cout << "ambil krs: ..." << endl;
            // Sleep(5*1000);
            mahasiswa *val = new mahasiswa(name, nim, gender);
            mhs->insertElem(*val);
            cout << "INPUT BERHASIL" << endl;
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
            cout << "TAMPILIN SEMUA DATA MAHASISWA (SORTED by NIM)" << endl;
        }
        else if(input == "4"){
            system("cls");
            cout << "Bye!\n" << endl;
            break;
        }else if(input == "cls" || input == "clear"){
            system("cls");
        }else{
            cout << "Input tidak valid: " << endl;
        }
    }
    
    return 0;
}