#include <string>
#include <stdlib.h>
#include <sstream>
#include "hashmap.hpp"

using namespace std;

hashmap::hashmap(){
    size = 0;
    for(int i = 0; i < MAX_SIZE; i++){
        map[i] = new DoublyLinkedList<mahasiswa>();
    }
}

int hashmap::keyToValue(string key){
    int n = key.length();
    string ans = key.substr(n-3,3);
    return stoi(ans);
}

void hashmap::insertElem(mahasiswa *value){
    int idx = h(keyToValue(value->getId()));
    
    map[idx]->tambahBelakang(value);
    size++;
}

Node<mahasiswa>* hashmap::searchElem(string id){
    int idx = h(keyToValue(id));
    return map[idx]->cari(id);
}

void hashmap::deleteElem(Node<mahasiswa>* hapus){
    int idx = h(keyToValue(hapus->data->getId()));
    map[idx]->hapus(hapus);
    size--;
}

void hashmap::updateName(Node<mahasiswa>* node, string name){
    node->data->setNama(name);
}

void hashmap::updateGender(Node<mahasiswa>* node, char jk){
    node->data->setGender(jk);
}

int hashmap::getSize(){
    return size;
}

// void hashmap::updateDosbing(Node<mahasiswa>* node){
//     node->data->setNama(name);
// }