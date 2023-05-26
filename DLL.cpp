#include <iostream>
#include "DLL.hpp"
using namespace std;

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
  head = nullptr;
  tail = nullptr;
}

template <typename T>
void DoublyLinkedList<T>::tambahBelakang(T* data) {
  Node<T>* nodeBaru = new Node<T>(data);
  if (head == nullptr) {
    head = nodeBaru;
    tail = nodeBaru;
  } else {
    nodeBaru->left = tail;
    nodeBaru->right = nullptr;
    tail->right = nodeBaru;
    tail = nodeBaru;
  }
}

template <typename T>
Node<T>* DoublyLinkedList<T>::cari(string id){
  Node<T> *temp = head;
  while(temp != nullptr && temp->data->getId() != id){
    temp = temp->right;
  }
  
  return temp;
}

template <typename T>
void DoublyLinkedList<T>::hapus(Node<T>* hapus) {
  if (head == tail) {
    delete head;
    head = nullptr;
    tail = nullptr;
  } else if (hapus->left == nullptr) {
    head = head->right;
    head->left = nullptr;
    delete hapus;
  } else if (hapus->right == nullptr) {
    tail = tail->left;
    tail->right = nullptr;
    delete hapus;
  } else {
    hapus->left->right = hapus->right;
    hapus->right->left = hapus->left;
    delete hapus;
  }
}