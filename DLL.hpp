#pragma once

#include "node.hpp"

template <typename T>
class DoublyLinkedList {
  private:
    Node<T>* head;
    Node<T>* tail;
  public:
    DoublyLinkedList();
    void tambahDepan(T);
    void tambahBelakang(T);
    void hapusDepan();
    void hapusBelakang();
};