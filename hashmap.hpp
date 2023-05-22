#pragma once

#include "model.hpp"
#include "DLL.hpp"
#define MAX_SIZE 97
#define h(k) k%MAX_SIZE

class hashmap
{
    private:
        int size;
        DoublyLinkedList<mahasiswa> *map[MAX_SIZE];
    public:
        hashmap();
        int keyToValue(std::string);
        void insertElem(mahasiswa); // input
        Node<mahasiswa>* searchElem(std::string); // search
        void deleteElem(Node<mahasiswa>*); // delete
        void updateName(Node<mahasiswa>*, std::string);
        void updateGender(Node<mahasiswa>*, char);
        void updateDosbing(Node<mahasiswa>*, int);
        // void addKRS(Node<mahasiswa>*, int);
        // void updateKRS(Node<mahasiswa>*, int);
        // void deleteKRS(Node<mahasiswa>*, int);
        // void traverse(); // status + all mhs
        // writeFile
};