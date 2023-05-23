#include <iostream>
#include "DLL.hpp"
using namespace std;

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
  head = NULL;
  tail = NULL;
}

template <typename T>
void DoublyLinkedList<T>::tambahDepan(T data) {
  Node<T>* nodeBaru = new Node<T>(data);
  
  if (head == NULL) {
    head = nodeBaru;
    tail = nodeBaru;
  } else {
    nodeBaru->right = head;
    head->left = nodeBaru;
    head = nodeBaru;
  }
}

template <typename T>
void DoublyLinkedList<T>::tambahBelakang(T data) {
  Node<T>* nodeBaru = new Node<T>(data);
  if (head == NULL) {
    head = nodeBaru;
    tail = nodeBaru;
  } else {
    nodeBaru->left = tail;
    tail->right = nodeBaru;
    tail = nodeBaru;
  }
}

template <typename T>
Node<T>* DoublyLinkedList<T>::cari(string id){
  Node<T> *temp = head;
  while(temp != NULL && temp->data.getId() != id){
    temp = temp->right;
  }
  
  return temp;
}

template <typename T>
void DoublyLinkedList<T>::hapus(Node<T>* hapus) {
  if (head == tail) {
    delete head;
    head = NULL;
    tail = NULL;
  } else if (hapus->left == NULL) {
    head = head->right;
    head->left = NULL;
    delete hapus;
  } else if (hapus->right == NULL) {
    tail = tail->left;
    tail->right = NULL;
    delete hapus;
  } else {
    hapus->left->right = hapus->right;
    hapus->right->left = hapus->left;
    delete hapus;
  }
}

// template <typename T>
// void DoublyLinkedList<T>::tampilData() {
//   Node* curr = head;
//   while (curr != NULL) {
//     cout << "Nama: " << curr->data.nama << endl;
//     cout << "NIM: " << curr->data.nim << endl;
//     cout << "Jurusan: " << curr->data.jurusan << endl;
//     cout << "Umur: " << curr->data.umur << endl;
//     cout << endl;
//     curr = curr->right;
//   }
// }