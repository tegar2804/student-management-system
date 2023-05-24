
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
#include <limits>
#include <ctime>
#include <sys/stat.h>

#include "model.hpp"
#include "myVector.hpp"
#include "hashmap.hpp"
#include "avl.hpp"

using namespace std;

void banner(){
    cout << "||========================================================|| " << endl;
    cout << "|| __          ________ _      _____ ____  __  __ ______  || " << endl;
    cout << "|| \\ \\        / /  ____| |    / ____/ __ \\|  \\/  |  ____| || " << endl;
    cout << "||  \\ \\  /\\  / /| |__  | |   | |   | |  | | \\  / | |__    || " << endl;
    cout << "||   \\ \\/  \\/ / |  __| | |   | |   | |  | | |\\/| |  __|   || " << endl;
    cout << "||    \\  /\\  /  | |____| |___| |___| |__| | |  | | |____  || " << endl;
    cout << "||     \\/  \\/   |______|______\\_____\\____/|_|  |_|______| || " << endl;
    cout << "||========================================================|| " << endl;
    cout << endl;
    cout << "Student Management System " << endl;    
}


void menu(){
    cout << endl;
    cout << "1. Masukkan Data Mahasiswa" << endl;
    cout << "2. Telusuri Data Mahasiswa" << endl;
    cout << "3. Tampilkan Semua" << endl;
    cout << "4. Simpan Dan Keluar" << endl;
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
        
        dosen* dosbing = lec->searchNode(lec->get_root(), *table->get(i)->get(3))->data;
        mahasiswa *temp = new mahasiswa(*table->get(i)->get(0), *table->get(i)->get(1), (*table->get(i)->get(2))[0], dosbing, list_krs);
        mhs->insertElem(temp);
        mhs_sorted->update_root(mhs_sorted->insert(mhs_sorted->get_root(), temp));
    }

    string input;
    while(true){
        menu();
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
                cin.ignore();
                getline(cin, name);
                if(!isLen(name)) cout << endl << "Input nama minimal mengandung 3 karakter!" << endl << endl;
                else if(name.length() > 45){
                    name = name.substr(0, 45);
                    cout << endl << "Input maksimal 45 karakter!" << endl << endl;
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
                else if(nim.length() > 15){
                    nim = nim.substr(0, 15);
                    cout << endl << "Input maksimal 15 karakter!" << endl << endl;
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
                if(temp != 1 && temp != 2){
                    cout << endl << "Input tidak valid!" << endl << endl ;
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
                cout << "Pilih Dosen Pembimbing:" << endl;
                for(int i = 0; i < qt; i++){
                    cout << i+1 << ". " << list_dosen->get(i)->getNama() << " (" << list_dosen->get(i)->getId() << ")" << endl;
                }
                cout << "0. Belum memiliki Dosen Pembimbing" << endl;
                cout << ">> ";
                cin >> dosbing;
                if(dosbing > 0 && dosbing <= qt){
                    cout << endl;
                    break;
                }else if(dosbing == 0){
                    cout << "Data Dosen Pembimbing Dikosongkan" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                } else{
                    cout << endl << "Input tidak valid!" << endl << endl ;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            mahasiswa *val = new mahasiswa(name, nim, gender, list_dosen->get(dosbing-1), new myVector<transkrip>());
            mhs->insertElem(val);
            mhs_sorted->update_root(mhs_sorted->insert(mhs_sorted->get_root(), val));
            cout << "Berhasil Menambahkan Data Mahasiswa!" << endl;
        }
        else if(input == "2"){
            while(true){
                try{
                    string search;
                    Node<mahasiswa>* node;
                    cout << "Masukkan NIM yang ingin dicari: ";
                    cin >> search;
                    if(search == "q" || search == "Q"){
                        break;                    
                    }else if(node = mhs->searchElem(search)){
                        mahasiswa *data = node->data;
                        int opt;
                        while(true){
                            cout << endl;
                            cout << "Nama Lengkap       : " << data->getNama() << endl;
                            cout << "NIM                : " << data->getId() << endl;
                            cout << "Jenis Kelamin      : " << ((data->getJk() == 'L') ? "Laki-laki" : "Perempuan") << endl;
                            if(data->getDosbing()){
                                cout << "Dosen Pembimbing   : " << data->getDosbing()->getNama() << " (" << data->getDosbing()->getId() << ")" << endl;
                            }else{
                                cout << "Dosen Pembimbing   : -" << endl;
                            }
                            printf("IP                 : %.2f \n", data->getIP());
                            if(data->getKRS()->size() == 0){
                                cout << "KRS                : - " << endl;
                            }else{
                                cout << "KRS                : ";
                                if(data->getKRS()->get(0)->getMutuDouble() >= 1){
                                    cout << 1 << ". " << data->getKRS()->get(0)->getMatkul()->getNama() << " (" << data->getKRS()->get(0)->getId() << ")    [tuntas|" << data->getKRS()->get(0)->getMutuChar() << "]" << endl;
                                }else{
                                    cout << 1 << ". " << data->getKRS()->get(0)->getMatkul()->getNama() << " (" << data->getKRS()->get(0)->getId() << ")    [belum tuntas| " << data->getKRS()->get(0)->getMutuChar() << "]" << endl;
                                }
                                for(int i = 1; i < data->getKRS()->size(); i++){
                                    if(data->getKRS()->get(i)->getMutuDouble() >= 1){
                                        cout << "                     " << i+1 << ". " << data->getKRS()->get(i)->getMatkul()->getNama() << " (" << data->getKRS()->get(i)->getId() << ")    [tuntas|" << data->getKRS()->get(i)->getMutuChar() << "]" << endl;
                                    }else{
                                        cout << "                     " << i+1 << ". " << data->getKRS()->get(i)->getMatkul()->getNama() << " (" << data->getKRS()->get(i)->getId() << ")    [belum tuntas| " << data->getKRS()->get(i)->getMutuChar() << "]" << endl;
                                    }
                                }
                            }
                            cout << endl;

                            cout << "------------------------------------" << endl;
                            cout << "1. Edit" << endl;
                            cout << "2. Delete" << endl;
                            cout << "3. Print" << endl;
                            cout << "0. Kembali" << endl;
                            cout << ">> ";
                            
                            cin >> opt;
                            if(opt == 1){
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                string nama, nim;
                                int gender;
                                cout << "|| Kosongkan Jika Tidak Ingin Mengedit ||" << endl;
                                cout << "Nama [" << data->getNama() << "]: ";
                                getline(cin, nama);
                                if(!isLen(nama)) cout << endl << "Data nama gagal diupdate!" << endl << endl;
                                else if(nama.length() > 45){
                                    nama = nama.substr(0, 45);
                                    data->setNama(nama);
                                    cout << endl << "Input maksimal 45 karakter!" << endl << endl;
                                }else{
                                    data->setNama(nama);
                                    cout << endl;
                                }

                                cout << "|| Kosongkan Jika Tidak Ingin Mengedit ||" << endl;
                                cout << "NIM [" << data->getId() << "]: ";
                                getline(cin, nim);
                                if(!isLen(nim)) cout << endl << "Data NIM gagal diupdate!" << endl << endl;
                                else if(!isId(nim)) cout << endl << "Input harus merupakan format nim (ex: X0123456)!" << endl << "Data NIM gagal diupdate!" << endl << endl;
                                else if(mhs->searchElem(nim)) cout << endl << "NIM sudah pernah digunakan!" << endl << "Data NIM gagal diupdate!" << endl << endl;
                                else if(nim.length() > 15){
                                    nim = nim.substr(0, 15);
                                    data->setNama(nim);
                                    cout << endl << "Input maksimal 15 karakter!" << endl << endl;
                                }else{
                                    data->setNama(nim);
                                    cout << endl;
                                }

                                cout << "|| Kosongkan Jika Tidak Ingin Mengedit ||" << endl;
                                cout << "Jenis Kelamin [" << ((data->getJk() == 'L') ? "Laki-laki" : "Perempuan") << "]: " << endl;
                                string str;
                                int temp;
                                cout << "Pilih Jenis Kelamin:" << endl; 
                                cout << "1. Laki-laki \t2. Perempuan" << endl;
                                cout << ">> ";
                                getline(cin, str);
                                if(isNum(str) && !&str) temp = stoi(str);
                                else temp = (data->getJk() == 'L') ? 1 : 2;
                                if(temp != 1 && temp != 2) cout << endl << "Input tidak valid!" << endl << endl ;
                                else{
                                    if(temp == 1) gender = 'L';
                                    else gender = 'P';
                                    data->setGender(gender);
                                    cout << endl;
                                }

                                cout << "|| Kosongkan Jika Tidak Ingin Mengedit ||" << endl;
                                myVector<dosen> *list_dosen = lec->inorder(lec->get_root());
                                int dosbing = -1, qt = list_dosen->size();
                                cout << "Pilih Dosen Pembimbing:" << endl;
                                for(int i = 0; i < qt; i++){
                                    if(data->getDosbing() && list_dosen->get(i)->getId() == data->getDosbing()->getId()) {
                                        dosbing = i+1;
                                        cout << i+1 << ". " << list_dosen->get(i)->getNama() << " (" << list_dosen->get(i)->getId() << ")  -> dosen pembimbing" << endl;
                                    }
                                    else cout << i+1 << ". " << list_dosen->get(i)->getNama() << " (" << list_dosen->get(i)->getId() << ")" << endl;
                                }
                                if(!data->getDosbing()){
                                    cout << "<< status: belum punya dosen pembimbing >>" << endl << endl;
                                }else{
                                    cout << "0. hapus dosen pembimbing" << endl;
                                    cout << "<< status: dosen pembimbing kamu saat ini " << data->getDosbing()->getNama() << " (" << data->getDosbing()->getId() << ") >>" << endl << endl;
                                } 
    
                                cout << ">> ";
                                string opsi;
                                getline(cin, opsi);
                                if(isNum(opsi) && (&str || str == "0") && stoi(opsi) >= 0 && stoi(opsi) <= qt) dosbing = stoi(opsi);
                                data->setDosbing(list_dosen->get(dosbing-1));
                                cout << endl;

                                myVector<matkul> *list_course = course->inorder(course->get_root());
                                qt = list_course->size();
                                bool taken[1024] = {0};
                                
                                while(true){
                                    cout << "Daftar Mata Kuliah:" << endl;
                                    for(int i = 0; i < (qt+1)/2; i++){
                                        if(taken[i+1] || data->getKRS()->search(list_course->get(i)->getId())){
                                            taken[i+1] = true;
                                            cout << i+1 << ". " << list_course->get(i)->getNama() << " (" << list_course->get(i)->getId() << "|" << list_course->get(i)->getSKS() << ") -> diambil";
                                            for(int j = 0; j < (max_matkul_len - ((i < 9 ? 3 : 4) + list_course->get(i)->getNama().length() + 2 + list_course->get(i)->getId().length() + 15)); j++)
                                                cout << " ";
                                        }else{
                                            taken[i+1] = false;
                                            cout << i+1 << ". " << list_course->get(i)->getNama() << " (" << list_course->get(i)->getId() << "|" << list_course->get(i)->getSKS() << ")";
                                            for(int j = 0; j < (max_matkul_len - ((i < 9 ? 3 : 4) + list_course->get(i)->getNama().length() + 2 + list_course->get(i)->getId().length() + 4)); j++)
                                                cout << " ";
                                        }
                                        if(i+((qt+1)/2) < qt){
                                            if(taken[i+((qt+1)/2)+1] || data->getKRS()->search(list_course->get(i+((qt+1)/2))->getId())){
                                                taken[i+((qt+1)/2)+1] = true;
                                                cout << i+((qt+1)/2)+1 << ". " << list_course->get(i+((qt+1)/2))->getNama() << " (" << list_course->get(i+((qt+1)/2))->getId() << "|" << list_course->get(i+((qt+1)/2))->getSKS() << ") -> diambil" << endl;
                                            }
                                            else{
                                                taken[i+((qt+1)/2)+1] = false;
                                                cout << i+((qt+1)/2)+1 << ". " << list_course->get(i+((qt+1)/2))->getNama() << " (" << list_course->get(i+((qt+1)/2))->getId() << "|" << list_course->get(i+((qt+1)/2))->getSKS() <<")" << endl;
                                            }
                                        }
                                    }
                                    cout << endl << endl;

                                    int opt;
                                    cout << "1. ambil\t2. hapus\t0. selesai" << endl;
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
                                        cout << endl << "| BL | A | AB | B | BC | C | D | E |" << endl << "Masukkan Nilai Mutu: ";
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
                                            cout << endl << "Mata Kuliah Sudah Diambil" << endl << endl;
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
                                            cout << endl << "Mata Kuliah Belum Diambil" << endl << endl;
                                            cin.clear();
                                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        }
                                    }else if(opt == 0){
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        cout << "Berhasil Meng-Update Data Mahasiswa!" << endl;
                                        break;
                                    }else{
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        cout << "Input tidak valid!" << endl;
                                    }
                                    data->recount_IP();
                                }
                            }else if(opt == 2){
                                mhs->deleteElem(node);
                                mhs_sorted->update_root(mhs_sorted->deleteNode(mhs_sorted->get_root(), mhs_sorted->searchNode(mhs_sorted->get_root(), data->getId())));
                                cout << endl << "Data Mahasiswa berhasil dihapus!" << endl;
                                break;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }else if(opt == 3){
                                time_t currentTime = time(nullptr);
                                myVector<string>* data_mhs = new myVector<string>();
                                {
                                string row = "Nama Lengkap       : " + data->getNama();
                                data_mhs->push(&row);
                                }
                                {
                                string row = "NIM                : " + data->getId();
                                data_mhs->push(&row);
                                }
                                {
                                string row = "Jenis Kelamin      : ";
                                row += ((data->getJk() == 'L') ? "Laki-laki" : "Perempuan");
                                data_mhs->push(&row);
                                }
                                if(data->getDosbing()){
                                    string row = "Dosen Pembimbing   : " + data->getDosbing()->getNama() + " (" + data->getDosbing()->getId() + ")";
                                    data_mhs->push(&row);
                                }else{
                                    string row = "Dosen Pembimbing   : -";
                                    data_mhs->push(&row);
                                }
                                {
                                string row = "IP                 : " + to_string(data->getIP());
                                data_mhs->push(&row);
                                }
                                if(data->getKRS()->size() == 0){
                                    string row = "KRS                : - ";
                                    data_mhs->push(&row);
                                }else{
                                    if(data->getKRS()->get(0)->getMutuDouble() >= 1){
                                        string row = "KRS                : 1. " + data->getKRS()->get(0)->getMatkul()->getNama() + " (" + data->getKRS()->get(0)->getId() + ")    [tuntas|" + data->getKRS()->get(0)->getMutuChar() + "]";
                                        data_mhs->push(&row);
                                    }else{
                                        string row = "KRS                : 1. " + data->getKRS()->get(0)->getMatkul()->getNama() + " (" + data->getKRS()->get(0)->getId() + ")    [belum tuntas"+ data->getKRS()->get(0)->getMutuChar() + "]";
                                        data_mhs->push(&row);
                                    }
                                    for(int i = 1; i < data->getKRS()->size(); i++){
                                        if(data->getKRS()->get(i)->getMutuDouble() >= 1){
                                            string row = "                     " + to_string(i+1) + ". " + data->getKRS()->get(i)->getMatkul()->getNama() + " (" + data->getKRS()->get(i)->getId() + ")    [tuntas|" + data->getKRS()->get(i)->getMutuChar() + "]";
                                            data_mhs->push(&row);
                                        }else{
                                            string row = "                     " + to_string(i+1) + ". " + data->getKRS()->get(i)->getMatkul()->getNama() + " (" + data->getKRS()->get(i)->getId() + ")    [belum tuntas|" + data->getKRS()->get(i)->getMutuChar() + "]";
                                            data_mhs->push(&row);
                                        }
                                    }
                                }
                                #ifdef _WIN32
                                    CreateDirectory("data_txt", NULL);
                                #else
                                    mkdir("data_txt", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                                #endif
                                writeTo(data_mhs, "data_txt/" + data->getId() + "_" + to_string(currentTime), "txt");
                                cout << "Berhasil Mencetak Data!!" << endl;
                                cout << "Silahkan Cek File \"data_txt/" + data->getId() + "_" + to_string(currentTime) + ".txt\"" << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                break;
                            }else if(opt != 0){
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Input tidak valid!" << endl;
                            }else{
                                break;
                            }
                        }
                    }else{
                        cout << "Mahasiswa tidak ditemukan" << endl;
                    }
                }catch (exception& e) {
                    #ifdef _WIN32
                        system("cls");
                    #else
                        system("clear");
                    #endif
                    cout << endl << "Input Error!" << endl << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << endl << " ====== Tekan \"Q\" untuk kembali ke menu utama! ====== " << endl << endl;
            }
        }
        else if(input == "3"){
            cout << "\t\t\t ========== Daftar Mahasiswa (SORTED by NIM) ==========" << endl;
            myVector<mahasiswa>* all_mhs = mhs_sorted->inorder(mhs_sorted->get_root());
            for(int i = 0; i < all_mhs->size(); i++){
                cout << all_mhs->get(i)->getId();
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
        }
        else if(input == "4"){
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
                system("cls");
            #else
                sleep(3);
                system("clear");
            #endif

            break;
        }else if(input == "cls" || input == "clear"){
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
        }else{
            cout << "Input tidak valid" << endl << endl;
        }
    }
    
    return 0;
}