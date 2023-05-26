
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define RESET   "\033[0m"
#define BLACK   "\033[0;1m"
#define DARK_RED     "\033[0;31m"
#define RED     "\033[31;1m"
#define DARK_GREEN   "\033[0;32m"
#define GREEN   "\033[32;1m"
#define DARK_YELLOW  "\033[0;33m"
#define YELLOW  "\033[33;1m"
#define BLUE    "\033[34;1m"
#define MAGENTA "\033[35;1m"
#define CYAN    "\033[36;1m"
#define WHITE   "\033[37;1m"

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <ctime>
#include <chrono>
#include <thread>
#include <sys/stat.h>

#include "model.hpp"
#include "myVector.hpp"
#include "hashmap.hpp"
#include "avl.hpp"

using namespace std;

void clear_terminal(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void banner(){
    clear_terminal();
    cout << BLUE << "\t\t=========================================================================" << endl;
    cout << CYAN << "\t\t   _____ __            __           __     ___                           " << endl;
    cout << CYAN << "\t\t  / ___// /___  ______/ /__  ____  / /_   /   | _____________  __________" << endl;
    cout << CYAN << "\t\t  \\__ \\/ __/ / / / __  / _ \\/ __ \\/ __/  / /| |/ ___/ ___/ _ \\/ ___/ ___/" << endl;
    cout << CYAN << "\t\t ___/ / /_/ /_/ / /_/ /  __/ / / / /_   / ___ / /__/ /__/  __(__  |__  ) " << endl;
    cout << CYAN << "\t\t/____/\\__/\\__,_/\\__,_/\\___/_/ /_/\\__/  /_/  |_\\___/\\___/\\___/____/____/  " << endl;
    cout << endl;
    cout << BLUE << "\t\t=======================" << CYAN << " Student Management System " << BLUE << "=======================" << RESET << endl;
    cout << endl;
}


void menu(){
    cout << MAGENTA << "<<" << RESET << " MENU UTAMA " << MAGENTA << ">>" << RESET << endl;
    cout << CYAN << "1) " << RESET << "Masukkan Data Mahasiswa" << endl;
    cout << CYAN << "2) " << RESET << "Cari Data Mahasiswa" << endl;
    cout << CYAN << "3) " << RESET << "Tampilkan Semua Data Mahasiswa" << endl;
    cout << RED << "0) " << RESET << "Simpan Dan Keluar" << RESET << endl;
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
    myVector<myVector<string>> *table = new myVector<myVector<string>>();  // Menyimpan table dari file CSV

    ifstream file(fname);  // Membuka file untuk dibaca

    string line;
    while (getline(file, line)) {
        myVector<string> *row = new myVector<string>();
        stringstream ss(line);
        string field;

        while (getline(ss, field, ';')) {
            row->push(&field);
        }
        
        table->push(row);
    }

    file.close();

    return table;
}

void writeTo(myVector<string>* data, string dest, string type){
    ofstream file(dest+"."+type);

    for (int i = 0; i < data->size(); i++) {
        file << *data->get(i) << "\n";
    }

    file.close();
}
                                             
int main(){
    banner();
    hashmap *mhs = new hashmap();
    avl<dosen> *lec = new avl<dosen>();
    avl<matkul> *course = new avl<matkul>();
    avl<mahasiswa> *mhs_sorted = new avl<mahasiswa>();
    
    // baca dari database dosen
    string file = "database/dosen.csv";
    myVector<myVector<string>>* table = readFile(&file[0]);
    for(int i = 0; i < table->size(); i++){
        dosen *temp = new dosen(*table->get(i)->get(0), *table->get(i)->get(1), (*table->get(i)->get(2))[0]);
        lec->update_root(lec->insert(lec->get_root(), temp));
    }
    
    int max_matkul_len = 0;
    // baca dari database matkul
    file = "database/matkul.csv";
    table = readFile(&file[0]);

    for(int i = 0; i < table->size(); i++){
        // gak penting
        if((4 + table->get(i)->get(0)->length() + 2 + table->get(i)->get(1)->length() + 15) > max_matkul_len) max_matkul_len = 4 + table->get(i)->get(0)->length() + 2 + table->get(i)->get(1)->length() + 15;

        matkul *temp = new matkul(*table->get(i)->get(0), *table->get(i)->get(1), stoi(*table->get(i)->get(2)));
        course->update_root(course->insert(course->get_root(), temp));
    }

    // baca dari database mahasiswa
    file = "database/mahasiswa.csv";
    table = readFile(&file[0]);
    for(int i = 0; i < table->size(); i++){ 
        myVector<transkrip> *list_krs = new myVector<transkrip>();
        for(int j = 4; j <= table->get(i)->size()-1; j++){
            double mutu;
            size_t pos1 = table->get(i)->get(j)->find("(");
            size_t pos2 = table->get(i)->get(j)->find(")");
            string code = table->get(i)->get(j)->substr(0,pos1);
            string val = table->get(i)->get(j)->substr(pos1+1,pos2-pos1-1);
            transkrip *temp = new transkrip(*table->get(i)->get(0), course->searchNode(course->get_root(), code)->data, val);
            list_krs->push(temp);
        }
        Node<dosen>* node_dosbing = lec->searchNode(lec->get_root(), *table->get(i)->get(3));
        dosen* dosbing = nullptr;
        if(node_dosbing) dosbing = node_dosbing->data;
        mahasiswa *temp = new mahasiswa(*table->get(i)->get(0), *table->get(i)->get(1), (*table->get(i)->get(2))[0], dosbing, list_krs);
        mhs->insertElem(temp);
        mhs_sorted->update_root(mhs_sorted->insert(mhs_sorted->get_root(), temp));
    }

    string input;
    while(true){
        menu();
        cout << ">> ";
        cin >> input;
        clear_terminal();
        if(input == "1"){
            banner();
            cout << MAGENTA << "<<" << RESET << " INPUT DATA MAHASISWA " << MAGENTA << ">>" << RESET << endl;
            string name, nim;
            char gender;
            int dosbing, krs;

            cout << YELLOW << "\n ====== Tekan \"" << RED << "Q" << YELLOW << "\" untuk batalkan input! ====== " << RESET << endl << endl;
            bool cancel = false;
            while(true){
                cout << BLUE << "+" << RESET << " Masukkan Nama: ";
                cin.ignore();
                getline(cin, name);
                if(name == "Q" || name == "q"){
                    cancel = true;
                    break;
                }
                if(!isLen(name)) cout << RED << endl << "| Input nama minimal mengandung 3 karakter! |" << RESET << endl << endl;
                else if(name.length() > 45){
                    name = name.substr(0, 45);
                    cout << YELLOW << endl << "| Input hanya menerima 45 karakter pertama! |" << RESET << endl << endl;
                    break;
                }else{
                    cout << endl;
                    break;
                }
            }

            if(cancel){
                banner();
                cout << RED << "| Input mahasiswa dibatalkan |" << RESET << endl << endl;
                continue;
            }
            
            while(true){
                cout << BLUE << "+" << RESET << " Masukkan NIM: ";
                getline(cin, nim);
                if(nim == "Q" || nim == "q"){
                    cancel = true;
                    break;
                }
                if(!isLen(nim)) cout << RED << endl << "| Input nama minimal mengandung 3 karakter! |" << RESET << endl << endl;
                else if(!isId(nim)) cout << RED << endl << "| Input harus merupakan format nim (ex: X0123456)! |" << RESET << endl << endl;
                else if(mhs->searchElem(nim)) cout << RED << endl << "| NIM sudah pernah digunakan! |" << RESET << endl << endl;
                else if(nim.length() > 15){
                    nim = nim.substr(0, 15);
                    cout << endl << YELLOW << "| Input maksimal 15 karakter! |" << RESET << endl << endl;
                    break;
                }else{
                    cout << endl;
                    break;
                }
            }

            if(cancel){
                banner();
                cout << RED << "| Input mahasiswa dibatalkan |" << RESET << endl << endl;
                continue;
            }

            cout << YELLOW << "WARNING: Input data mahasiswa sudah tidak bisa dibatalkan" << endl << endl;

            while(true){
                int temp;
                cout << BLUE << "+" << RESET << " Pilih Jenis Kelamin:"; 
                cout << "\n" << CYAN << "(1) " << RESET << "Laki-laki\n" << MAGENTA << "(2) " << RESET << "Perempuan" << endl;
                cout << ">> ";
                cin >> temp;
                if(temp != 1 && temp != 2){
                    cout << endl << RED << "| Input tidak valid! |" << RESET << endl << endl ;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }else{
                    if(temp == 1) gender = 'L';
                    else gender = 'P';
                    cout << endl;
                    break;
                }
            }

            myVector<dosen> *list_dosen = lec->inorder(lec->get_root());
            while(true){
                int qt = list_dosen->size();
                cout << BLUE << "+" << RESET << " Pilih Dosen Pembimbing:" << endl;
                for(int i = 0; i < qt; i++){
                    cout << CYAN << i+1 << ". " << RESET << list_dosen->get(i)->getNama() << " (" << list_dosen->get(i)->getId() << ")" << endl;
                }
                cout << RED << "0."<< RESET << " Belum memiliki Dosen Pembimbing" << endl;
                cout << ">> ";
                cin >> dosbing;
                if(dosbing > 0 && dosbing <= qt){
                    cout << endl;
                    break;
                }else if(dosbing == 0){
                    cout << YELLOW << "| Data Dosen Pembimbing Dikosongkan |" << RESET << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                } else{
                    cout << endl << RED << "| Input tidak valid! |" << RESET << endl << endl ;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            mahasiswa *val = new mahasiswa(name, nim, gender, list_dosen->get(dosbing-1), new myVector<transkrip>());
            mhs->insertElem(val);
            mhs_sorted->update_root(mhs_sorted->insert(mhs_sorted->get_root(), val));

            cout << GREEN << "| Berhasil Menambahkan Data Mahasiswa! |" << endl << endl;
            cout << YELLOW << "> MOHON TUNGGU!" << endl;
            #ifdef _WIN32
                Sleep(2000);
            #else
                sleep(2);
            #endif
            banner();
        }
        else if(input == "2"){
            banner();
            while(true){
                try{
                    cout << MAGENTA << "<<" << RESET << " CARI DATA MAHASISWA " << MAGENTA << ">>" << RESET << endl;
                    string search;
                    Node<mahasiswa>* node;
                    cout << YELLOW << "\n ====== Tekan \"" << RED << "Q" << YELLOW << "\" untuk kembali ke menu utama! ====== " << RESET << endl << endl;
                    cout << BLUE << "+" << RESET << " Masukkan NIM yang ingin dicari: ";
                    cin >> search;
                    if(search == "q" || search == "Q"){
                        banner();
                        break;
                    }else if(node = mhs->searchElem(search)){
                        mahasiswa *data = node->data;
                        int opt;
                        while(true){
                            banner();
                            cout << MAGENTA << "<<" << RESET << " CARI DATA MAHASISWA " << MAGENTA << ">>" << RESET << endl << endl;
                            cout << BLUE << "+" << RESET << " Masukkan NIM yang ingin dicari: " << data->getId() << endl;
                            cout << "------------------------------------------------------------------------------------------------------------" << endl;
                            cout << BLUE << "+ " << RESET << "Nama Lengkap       : " << data->getNama() << endl;
                            cout << BLUE << "+ " << RESET << "NIM                : " << data->getId() << endl;
                            cout << BLUE << "+ " << RESET << "Jenis Kelamin      : " << ((data->getJk() == 'L') ? "Laki-laki" : "Perempuan") << endl;
                            if(data->getDosbing()){
                                cout << BLUE << "+ " << RESET << "Dosen Pembimbing   : " << data->getDosbing()->getNama() << " (" << data->getDosbing()->getId() << ")" << endl;
                            }else{
                                cout << BLUE << "+ " << RESET << "Dosen Pembimbing   : -" << endl;
                            }
                            cout << BLUE << "+ " << RESET;
                            printf("IP                 : %.2f \n", data->getIP());
                            if(data->getKRS()->size() == 0){
                                cout << BLUE << "+ " << RESET << "Rekapitulasi Studi : - " << endl;
                            }else{
                                cout << BLUE << "+ " << RESET << "Rekapitulasi Studi : ";
                                if(data->getKRS()->get(0)->getMutuDouble() >= 1){
                                    cout << 1 << ". " << data->getKRS()->get(0)->getMatkul()->getNama() << " (" << data->getKRS()->get(0)->getId() << ")    " << GREEN << "[tuntas|" << data->getKRS()->get(0)->getMutuChar() << "]" << RESET << endl;
                                }else{
                                    cout << 1 << ". " << data->getKRS()->get(0)->getMatkul()->getNama() << " (" << data->getKRS()->get(0)->getId() << ")    " << RED << "[belum tuntas| " << data->getKRS()->get(0)->getMutuChar() << "]" << RESET << endl;
                                }
                                for(int i = 1; i < data->getKRS()->size(); i++){
                                    if(data->getKRS()->get(i)->getMutuDouble() >= 1){
                                        cout << "                       " << i+1 << ". " << data->getKRS()->get(i)->getMatkul()->getNama() << " (" << data->getKRS()->get(i)->getId() << ")    " << GREEN << "[tuntas|" << data->getKRS()->get(i)->getMutuChar() << "]" << RESET << endl;
                                    }else{
                                        cout << "                       " << i+1 << ". " << data->getKRS()->get(i)->getMatkul()->getNama() << " (" << data->getKRS()->get(i)->getId() << ")    " << RED << "[belum tuntas| " << data->getKRS()->get(i)->getMutuChar() << "]" << RESET << endl;
                                    }
                                }
                            }
                            cout << endl;

                            cout << "------------------------------------------------------------------------------------------------------------" << endl;
                            cout << YELLOW << "1. Edit" << endl;
                            cout << RED << "2. Delete" << endl;
                            cout << GREEN << "3. Print" << endl;
                            cout << RED << "0. Kembali" << RESET << endl;
                            cout << ">> ";
                            
                            cin >> opt;
                            if(opt == 1){
                                banner();
                                cout << MAGENTA << "<<" << RESET << " EDIT DATA MAHASISWA " << MAGENTA << ">>" << RESET << endl << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                string nama, nim;
                                int gender;
                                cout << YELLOW << "|| Kosongkan Jika Tidak Ingin Mengedit ||" << RESET << endl << endl;
                                cout << CYAN << "+ " << RESET << "Nama [" << YELLOW << data->getNama() << RESET << "]: ";
                                getline(cin, nama);
                                if(!isLen(nama)) cout << endl << RED << "| Data nama gagal diupdate! |" << RESET << endl << endl;
                                else if(nama.length() > 45){
                                    nama = nama.substr(0, 45);
                                    data->setNama(nama);
                                    cout << endl << YELLOW << "| Input maksimal 45 karakter! |" << RESET << endl << endl;
                                }else{
                                    data->setNama(nama);
                                    cout << endl;
                                }

                                cout << YELLOW << "|| Kosongkan Jika Tidak Ingin Mengedit ||" << RESET << endl << endl;
                                cout << CYAN << "+ " << RESET << "NIM [" << YELLOW << data->getId() << RESET << "]: ";
                                getline(cin, nim);
                                if(!isLen(nim)) cout << endl << RED << "| Data NIM gagal diupdate! |" << RESET << endl << endl;
                                else if(!isId(nim)) cout << endl << RED << "| Input harus merupakan format nim (ex: X0123456)! |" << endl << "Data NIM gagal diupdate!" << RESET << endl << endl;
                                else if(mhs->searchElem(nim)) cout << endl << RED << "| NIM sudah pernah digunakan! |" << endl << "Data NIM gagal diupdate!" << RESET << endl << endl;
                                else if(nim.length() > 15){
                                    nim = nim.substr(0, 15);
                                    data->setNama(nim);
                                    cout << endl << YELLOW << "| Input maksimal 15 karakter! |" << RESET << endl << endl;
                                }else{
                                    data->setNama(nim);
                                    cout << endl;
                                }

                                cout << CYAN << "+ " << RESET << "Jenis Kelamin [" << YELLOW << ((data->getJk() == 'L') ? "Laki-laki" : "Perempuan") << RESET << "]: " << endl;
                                string str;
                                int temp;
                                cout << "Pilih Jenis Kelamin:" << endl; 
                                cout << BLUE << "(1)" << RESET << " Laki-laki \n";
                                cout << MAGENTA << "(2)" << RESET << " Perempuan" << endl;
                                cout << ">> ";
                                getline(cin, str);
                                if(isNum(str)) temp = stoi(str);
                                else temp = (data->getJk() == 'L') ? 1 : 2;
                                if(temp != 1 && temp != 2) cout << endl << RED << "| Input tidak valid! |" << RESET << endl << endl ;
                                else{
                                    if(temp == 1) gender = 'L';
                                    else gender = 'P';
                                    data->setGender(gender);
                                    cout << endl;
                                }

                                myVector<dosen> *list_dosen = lec->inorder(lec->get_root());
                                int dosbing = 0, qt = list_dosen->size();
                                cout << CYAN << "+ " << RESET << "Pilih Dosen Pembimbing:" << endl;
                                for(int i = 0; i < qt; i++){
                                    if(data->getDosbing() && list_dosen->get(i)->getId() == data->getDosbing()->getId()) {
                                        dosbing = i+1;
                                        cout << BLUE << i+1 << ". " << RESET << list_dosen->get(i)->getNama() << " (" << list_dosen->get(i)->getId() << ")" << GREEN << "  -> dosen pembimbing" << RESET << endl;
                                    }
                                    else cout << BLUE << i+1 << ". " << RESET << list_dosen->get(i)->getNama() << " (" << list_dosen->get(i)->getId() << ")" << endl;
                                }
                                if(!data->getDosbing()){
                                    cout << YELLOW << "<< status: belum punya dosen pembimbing >>" << RESET << endl << endl;
                                }else{
                                    cout << RED << "0. " << RESET << "hapus dosen pembimbing" << endl;
                                    cout << GREEN << "<< status: dosen pembimbing kamu saat ini " << data->getDosbing()->getNama() << " (" << data->getDosbing()->getId() << ") >>" << RESET << endl << endl;
                                } 
    
                                cout << ">> ";
                                string opsi;
                                getline(cin, opsi);
                                
                                if(isNum(opsi) && stoi(opsi) >= 0 && stoi(opsi) <= qt) dosbing = stoi(opsi);
                                else dosbing = 0;
                                data->setDosbing(list_dosen->get(dosbing-1));
                                cout << endl;

                                myVector<matkul> *list_course = course->inorder(course->get_root());
                                qt = list_course->size();
                                bool taken[1024] = {0};
                                
                                while(true){
                                    cout << CYAN << "+ " << RESET << "Daftar Mata Kuliah:" << endl;
                                    for(int i = 0; i < (qt+1)/2; i++){
                                        if(taken[i+1] || data->getKRS()->search(list_course->get(i)->getId())){
                                            taken[i+1] = true;
                                            cout << BLUE << i+1 << ". " << RESET << list_course->get(i)->getNama() << " (" << list_course->get(i)->getId() << "|" << list_course->get(i)->getSKS() << ")" << GREEN << " -> diambil" << RESET;
                                            for(int j = 0; j < (max_matkul_len - ((i < 9 ? 3 : 4) + list_course->get(i)->getNama().length() + 2 + list_course->get(i)->getId().length() + 15)); j++)
                                                cout << " ";
                                        }else{
                                            taken[i+1] = false;
                                            cout << BLUE << i+1 << ". " << RESET << list_course->get(i)->getNama() << " (" << list_course->get(i)->getId() << "|" << list_course->get(i)->getSKS() << ")";
                                            for(int j = 0; j < (max_matkul_len - ((i < 9 ? 3 : 4) + list_course->get(i)->getNama().length() + 2 + list_course->get(i)->getId().length() + 4)); j++)
                                                cout << " ";
                                        }
                                        if(i+((qt+1)/2) < qt){
                                            if(taken[i+((qt+1)/2)+1] || data->getKRS()->search(list_course->get(i+((qt+1)/2))->getId())){
                                                taken[i+((qt+1)/2)+1] = true;
                                                cout << BLUE << i+((qt+1)/2)+1 << ". " << RESET << list_course->get(i+((qt+1)/2))->getNama() << " (" << list_course->get(i+((qt+1)/2))->getId() << "|" << list_course->get(i+((qt+1)/2))->getSKS() << ") " << GREEN << "-> diambil" << RESET << endl;
                                            }
                                            else{
                                                taken[i+((qt+1)/2)+1] = false;
                                                cout << BLUE << i+((qt+1)/2)+1 << ". " << RESET << list_course->get(i+((qt+1)/2))->getNama() << " (" << list_course->get(i+((qt+1)/2))->getId() << "|" << list_course->get(i+((qt+1)/2))->getSKS() <<")" << endl;
                                            }
                                        }
                                    }
                                    cout << endl << endl;

                                    int opt;
                                    cout << GREEN << "1. tambah" << RED << "\t2. hapus\t0. selesai" << RESET << endl;
                                    cout << ">> ";
                                    cin >> opt;
                                    if(opt == 1){
                                        int opt_matkul;
                                        cout << endl << "Pilih Mata Kuliah (sesuai nomor): ";
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        cin >> opt_matkul;
                                        cout << endl;
                                        
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                        double mutu;
                                        string val;
                                        cout << endl << "|(BL)|" << DARK_GREEN << "(A)" << RESET << "|" << GREEN << "(AB)" <<  RESET << "|";
                                        cout << DARK_YELLOW << "(B)" <<  RESET << "|" << DARK_YELLOW << "(BC)" << RESET << "|";
                                        cout << YELLOW << "(C)" << RESET << "|";
                                        cout << RED << "(D)" <<  RESET << "|" << RED << "(E)" << RESET << "|" << endl << CYAN << "+ " << RESET << "Masukkan Nilai Mutu: ";
                                        cin >> val;
                                        cout << endl;
                                        if(val != "A" && val != "AB" && val != "B" && val != "BC" && val != "C" && val != "D" && val != "E" && val != "BL"){
                                            cout << "Input Gagal!" << endl;
                                            continue;
                                        }
                                        if(!taken[opt_matkul]){
                                            transkrip* temp = new transkrip(data->getId(), list_course->get(opt_matkul-1), val);
                                            data->addKRS(temp);
                                            taken[opt_matkul] = true;
                                        }else{
                                            cout << endl << YELLOW << "| Mata Kuliah Sudah Diambil |" << RESET << endl << endl;
                                            cin.clear();
                                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        }
                                    }else if(opt == 2){
                                        int opt_matkul;
                                        cout << endl << "Pilih Mata Kuliah (sesuai nomor): ";
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        cin >> opt_matkul;
                                        cout << endl;
                                        if(taken[opt_matkul]){
                                            taken[opt_matkul] = false;
                                            data->deleteKRS(list_course->get(opt_matkul-1)->getId());
                                        } else{
                                            cout << endl << YELLOW << "| Mata Kuliah Belum Diambil |" << RESET << endl << endl;
                                            cin.clear();
                                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        }
                                    }else if(opt == 0){
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        cout << GREEN << "| Berhasil Meng-Update Data Mahasiswa! |" << RESET << endl;
                                        cout << YELLOW << "> MOHON TUNGGU!" << endl;
                                        #ifdef _WIN32
                                            Sleep(2000);
                                        #else
                                            sleep(2);
                                        #endif
                                        break;
                                    }else{
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        cout << RED << "| Input tidak valid! |" << RESET << endl;
                                    }
                                    data->recount_IP();
                                }
                            }else if(opt == 2){
                                mhs->deleteElem(node);
                                mhs_sorted->update_root(mhs_sorted->deleteNode(mhs_sorted->get_root(), mhs_sorted->searchNode(mhs_sorted->get_root(), data->getId())));
                                banner();
                                cout << endl << RED << "| Data Mahasiswa berhasil dihapus! |" << RESET << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                break;
                            }else if(opt == 3){
                                myVector<string>* data_mhs = new myVector<string>();
                                {
                                string row = "+ Nama Lengkap       : " + data->getNama();
                                data_mhs->push(&row);
                                }
                                {
                                string row = "+ NIM                : " + data->getId();
                                data_mhs->push(&row);
                                }
                                {
                                string row = "+ Jenis Kelamin      : ";
                                row += ((data->getJk() == 'L') ? "Laki-laki" : "Perempuan");
                                data_mhs->push(&row);
                                }
                                if(data->getDosbing()){
                                    string row = "+ Dosen Pembimbing   : " + data->getDosbing()->getNama() + " (" + data->getDosbing()->getId() + ")";
                                    data_mhs->push(&row);
                                }else{
                                    string row = "+ Dosen Pembimbing   : -";
                                    data_mhs->push(&row);
                                }
                                {
                                string row = "+ IP                 : " + to_string(data->getIP());
                                data_mhs->push(&row);
                                }
                                if(data->getKRS()->size() == 0){
                                    string row = "+ Rekapitulasi Studi : - ";
                                    data_mhs->push(&row);
                                }else{
                                    if(data->getKRS()->get(0)->getMutuDouble() >= 1){
                                        string row = "+ Rekapitulasi Studi : 1. " + data->getKRS()->get(0)->getMatkul()->getNama() + " (" + data->getKRS()->get(0)->getId() + ")    [tuntas|" + data->getKRS()->get(0)->getMutuChar() + "]";
                                        data_mhs->push(&row);
                                    }else{
                                        string row = "+ Rekapitulasi Studi : 1. " + data->getKRS()->get(0)->getMatkul()->getNama() + " (" + data->getKRS()->get(0)->getId() + ")    [belum tuntas"+ data->getKRS()->get(0)->getMutuChar() + "]";
                                        data_mhs->push(&row);
                                    }
                                    for(int i = 1; i < data->getKRS()->size(); i++){
                                        if(data->getKRS()->get(i)->getMutuDouble() >= 1){
                                            string row = "                       " + to_string(i+1) + ". " + data->getKRS()->get(i)->getMatkul()->getNama() + " (" + data->getKRS()->get(i)->getId() + ")    [tuntas|" + data->getKRS()->get(i)->getMutuChar() + "]";
                                            data_mhs->push(&row);
                                        }else{
                                            string row = "                       " + to_string(i+1) + ". " + data->getKRS()->get(i)->getMatkul()->getNama() + " (" + data->getKRS()->get(i)->getId() + ")    [belum tuntas|" + data->getKRS()->get(i)->getMutuChar() + "]";
                                            data_mhs->push(&row);
                                        }
                                    }
                                }
                                #ifdef _WIN32
                                    CreateDirectory("data_txt", NULL);
                                #else
                                    mkdir("data_txt", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                                #endif
                                time_t currentTime = time(nullptr);
                                string filename = "data_txt/" + data->getId() + "_" + to_string(currentTime);
                                writeTo(data_mhs, filename, "txt");
                                banner();
                                cout << GREEN << "| Berhasil Mencetak Data |" << RESET << endl;
                                cout << YELLOW << "> Silahkan Cek File \"" << RED << filename << ".txt" << YELLOW << "\"" << RESET << endl;
                                cout << YELLOW << "> Tutup file untuk kembali!" << endl;
                                string command = "gedit " + filename + ".txt";
                                system(command.c_str());
                                banner();
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                break;
                            }else if(opt != 0){
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                banner();
                                cout << "| Input tidak valid! |" << endl;
                            }else{
                                banner();
                                break;
                            }
                        }
                    }else{
                        banner();
                        cout << endl << YELLOW << "| Mahasiswa tidak ditemukan! |" << RESET << endl << endl;
                    }
                }catch (exception& e) {
                    banner();
                    cout << endl << RED << "> WARNING: Input Error!" << RESET << endl << endl;
                    cout << endl << YELLOW << "> Enter untuk kembali ke manu!" << RESET << endl << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
        }
        else if(input == "3"){
            while(true){
                banner();
                cout << MAGENTA << "<<" << RESET << " Daftar Seluruh Mahasiswa " << MAGENTA << ">>" << RESET << endl;
                myVector<mahasiswa>* all_mhs = mhs_sorted->inorder(mhs_sorted->get_root());
                cout << "| NIM             | NAMA                                          | IP   | DOSEN PEMBIMBING " << endl;
                cout << "|-----------------|-----------------------------------------------|------|--------------------------------" << endl;
                for(int i = 0; i < all_mhs->size(); i++){
                    cout << "| " << all_mhs->get(i)->getId();
                    for(int j = 0; j < 15-all_mhs->get(i)->getId().size(); j++) cout << " ";
                    cout << " | " << all_mhs->get(i)->getNama();
                    for(int j = 0; j < 45-all_mhs->get(i)->getNama().size(); j++) cout << " ";
                    printf(" | %.2f", all_mhs->get(i)->getIP());
                    if(all_mhs->get(i)->getDosbing()){
                        cout << " | " << all_mhs->get(i)->getDosbing()->getNama();
                        cout << " (" << all_mhs->get(i)->getDosbing()->getId() << ")" << endl;
                    }else{
                        cout << " | - " << endl;
                    }
                }
                cout << endl << "Jumlah Seluruh Mahasiswa: " << mhs->getSize() << endl << endl;
                int opt;
                cout << GREEN << "1. print" << RESET << endl;
                cout << RED << "0. kembali" << RESET << endl;
                cout << ">> ";
                cin >> opt;
                if(opt == 1){
                    myVector<string>* data_mhs = new myVector<string>();
                    {
                    string first_row = "| NIM             | NAMA                                          | IP   | DOSEN PEMBIMBING ";
                    data_mhs->push(&first_row);
                    }
                    {
                    string first_row = "|-----------------|-----------------------------------------------|------|--------------------------------";
                    data_mhs->push(&first_row);
                    }
                    for(int i = 0; i < all_mhs->size(); i++){
                        string row = "| ";
                        row += all_mhs->get(i)->getId();
                        for(int j = 0; j < 15-all_mhs->get(i)->getId().size(); j++) row += " ";
                        row += " | " + all_mhs->get(i)->getNama();
                        for(int j = 0; j < 45-all_mhs->get(i)->getNama().size(); j++) row += " ";
                        row += " | ";
                        string strValue = to_string(all_mhs->get(i)->getIP());
                        row += strValue.substr(0, 4);
                        if(all_mhs->get(i)->getDosbing()){
                            row += " | " + all_mhs->get(i)->getDosbing()->getNama();
                            row += " (" + all_mhs->get(i)->getDosbing()->getId() + ")";
                        }else{
                            row += " | - ";
                        }
                        data_mhs->push(&row);
                    }
                    #ifdef _WIN32
                        CreateDirectory("data_txt", NULL);
                    #else
                        mkdir("data_txt", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                    #endif
                    time_t currentTime = time(nullptr);
                    string filename = "data_txt/all_mahasiswa_" + to_string(currentTime);
                    writeTo(data_mhs, filename, "txt");
                    banner();
                    cout << GREEN << "| Berhasil Mencetak Data |" << RESET << endl;
                    cout << YELLOW << "> Silahkan Cek File \"" << RED << filename << ".txt" << YELLOW << "\"" << RESET << endl;
                    cout << YELLOW << "> Tutup file untuk kembali ke menu utama!" << endl;
                    string command = "gedit " + filename + ".txt";
                    system(command.c_str());
                    banner();
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }else if(opt == 0){
                    banner();
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }else{
                    banner();
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        else if(input == "0"){
            cout << endl << "Terima Kasih Sudah Mencoba!\n" << endl;
            myVector<mahasiswa>* all_mhs = mhs_sorted->inorder(mhs_sorted->get_root());
            myVector<string>* all_mhs_str = new myVector<string>();
            for(int i = 0; i < all_mhs->size(); i++){
                string row = "";
                row += all_mhs->get(i)->getNama()+";";
                row += all_mhs->get(i)->getId()+";";
                row += all_mhs->get(i)->getJk();
                row += ";";
                if(all_mhs->get(i)->getDosbing()) row += all_mhs->get(i)->getDosbing()->getId() + ";";
                else row += "-;";
                for(int j = 0; j < all_mhs->get(i)->getKRS()->size() ; j++){
                    row += all_mhs->get(i)->getKRS()->get(j)->getId()+ "(" + all_mhs->get(i)->getKRS()->get(j)->getMutuChar() + ")" + ";";
                }
                
                all_mhs_str->push(&row);
            }
            
            myVector<dosen>* all_dos = lec->inorder(lec->get_root());
            myVector<string>* all_dos_str = new myVector<string>();
            for(int i = 0; i < all_dos->size(); i++){
                string row = "";
                row += all_dos->get(i)->getNama()+";";
                row += all_dos->get(i)->getId()+";";
                row += all_dos->get(i)->getJk();
                row += ";";
                
                all_dos_str->push(&row);
            }
            
            myVector<matkul>* all_mat = course->inorder(course->get_root());
            myVector<string>* all_mat_str = new myVector<string>();
            for(int i = 0; i < all_mat->size(); i++){
                string row = "";
                row += all_mat->get(i)->getNama()+";";
                row += all_mat->get(i)->getId()+";";
                row += to_string(all_mat->get(i)->getSKS())+ ";";
                all_mat_str->push(&row);
            }

            writeTo(all_mhs_str, "database/mahasiswa", "csv");
            writeTo(all_dos_str, "database/dosen", "csv");
            writeTo(all_mat_str, "database/matkul", "csv");
            #ifdef _WIN32
                Sleep(3000);
            #else
                sleep(3);
            #endif
            clear_terminal();

            break;
        }else{
            banner();
            cout << RED << "| Input tidak valid |" << endl << endl;
        }
    }
    
    return 0;
}