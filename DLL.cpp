#include <iostream>
#include "model.hpp"
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
  if (tail == NULL) {
    head = nodeBaru;
    tail = nodeBaru;
  } else {
    nodeBaru->left = tail;
    tail->right = nodeBaru;
    tail = nodeBaru;
  }
}

template <typename T>
void DoublyLinkedList<T>::hapusDepan() {
  if (head == NULL) {
    return;
  } else if (head == tail) {
    delete head;
    head = NULL;
    tail = NULL;
  } else {
    Node<T>* nodeHapus = head;
    head = head->right;
    head->left = NULL;
    delete nodeHapus;
  }
}

template <typename T>
void DoublyLinkedList<T>::hapusBelakang() {
  if (tail == NULL) {
    return;
  } else if (head == tail) {
    delete tail;
    head = NULL;
    tail = NULL;
  } else {
    Node<T>* nodeHapus = tail;
    tail = tail->left;
    tail->right = NULL;
    delete nodeHapus;
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