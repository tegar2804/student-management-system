
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

// #include "hashmap.h"
// #include "model.h"

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
    cout << "4. Simpan Perubahan Data Mahasiswa (?)" << endl;
    cout << "5. Kembali" << endl;
    cout << "Masukkan input anda: " << endl;
}

void readFile(char* fname){
    FILE *file = fopen(fname, "r");
 
	if(!file)
	{
		printf("Gagal saat membuka file!\n");
		exit(0);
	}
 
	char content[1024];
	while(fgets(content, 1024, file))
	{
		char *v = strtok(content, ",");
		while(v)
		{
			printf("%s ", v);
			v = strtok(NULL, ",");
		}
		printf("\n");
	}
	fclose(file);

    // return content;
}
                                             
int main(){
    banner();
    string input;
    while(true){
        option();
        cout << ">> ";
        cin >> input;
        cout << input << endl;
        exit(0);
        if(input == "1"){
            cout << "INPUT DATA" << endl;
            cout << "===============" << endl;
            cout << "masukkan nama: " << endl;
            cout << "masukkan NIM: " << endl;
            cout << "pilih gender: 1. laki-laki 2. perempuan" << endl;
            cout << "pilih dosbing: ..." << endl;
            cout << "ambil krs: ..." << endl;
            Sleep(5*1000);
            cout << "INPUT BERHASIL" << endl;
        }
        else if(input == "2"){
            while(true){
                string search;
                cout << "Cari Mahasiswa" << endl;
                cout << "===============" << endl;
                cout << "masukkan NIM: " << endl;
                cin >> search;
                if(search == "q"){
                    break;
                // fungsi cari blom dibuat
                }else if(true){
                    cout << "1. Edit" << endl;
                    cout << "2. Delete" << endl;
                    cout << "3. Kembali" << endl;
                }else{
                    cout << "Mahasiswa tidak ditemukan" << endl;
                } 
                cout << "tekan \"q\" untuk kembali!" << endl;
            }
        }
        else if(input == "3"){
            cout << "TAMPILIN JUMLAH MAHASISWA" << endl;
            cout << "TAMPILIN SEMUA DATA MAHASISWA (SORTED by NIM)" << endl;
        }
        else if(input == "4"){
            cout << "Perubahan Telah Tersimpan!" << endl;
        }
        else if(input == "5"){
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