#include "hashmap.hpp"
#include "model.hpp"
#include "avl.hpp"
#include <string>
#include <stdlib.h>

using namespace std;

hashmap::hashmap(){
    size = 0;
    for(int i = 0; i < MAX_SIZE; i++){
        map[i] = NULL;
    }
}

int hashmap::keyToValue(string key){
    int n = key.length();
    string ans = key.substr(n-4,3);
    return stoi(ans);
}

void hashmap::insertElem(student value){
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->val = value;
    newNode->right = NULL;
    newNode->left = NULL;
    
    int idx = h(keyToValue(value.getId()));

    
}