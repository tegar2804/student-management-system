#pragma once

#include "node.hpp"
#define MAX_SIZE 97
#define h(k) k%MAX_SIZE

class hashmap
{
    private:
        int size;
        struct node *map[MAX_SIZE];
    public:
        hashmap();
        int keyToValue(string);
        void insertElem(student); // input
        struct node* searchElem(string); // search
        string deleteElem(string); // delete
        void updateElem(); // edit
        void traverse(); // status + all mhs
        // writeFile
};