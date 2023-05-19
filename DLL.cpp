#include <iostream>
#include "model.hpp"
using namespace std;

#include "DLL.hpp"

// Pemanggilan konstruktor default
DoublyLinkedList::DoublyLinkedList() {
  head = NULL;
  tail = NULL;
}

void DoublyLinkedList::tambahDepan(student data) {
  Node* nodeBaru = new Node(data);
  if (head == NULL) {
    head = nodeBaru;
    tail = nodeBaru;
  } else {
    nodeBaru->right = head;
    head->left = nodeBaru;
    head = nodeBaru;
  }
}

void DoublyLinkedList::tambahBelakang(student data) {
  Node* nodeBaru = new Node(data);
  if (tail == NULL) {
    head = nodeBaru;
    tail = nodeBaru;
  } else {
    nodeBaru->left = tail;
    tail->right = nodeBaru;
    tail = nodeBaru;
  }
}

void DoublyLinkedList::hapusDepan() {
  if (head == NULL) {
    return;
  } else if (head == tail) {
    delete head;
    head = NULL;
    tail = NULL;
  } else {
    Node* nodeHapus = head;
    head = head->right;
    head->left = NULL;
    delete nodeHapus;
  }
}

void DoublyLinkedList::hapusBelakang() {
  if (tail == NULL) {
    return;
  } else if (head == tail) {
    delete tail;
    head = NULL;
    tail = NULL;
  } else {
    Node* nodeHapus = tail;
    tail = tail->left;
    tail->right = NULL;
    delete nodeHapus;
  }
}

// void DoublyLinkedList::tampilData() {
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