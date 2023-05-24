#pragma once

#include "model.hpp"
#include "node.hpp"

template <typename T>
class DoublyLinkedList {
  private:
    Node<T> *head;
    Node<T> *tail;
  public:
    DoublyLinkedList();
    void tambahBelakang(T*);
    Node<T>* cari(std::string);
    void hapus(Node<T>*);
};

template class DoublyLinkedList<mahasiswa>;