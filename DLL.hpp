#pragma once

#include "node.hpp"

class DoublyLinkedList {
  private:
    Node* head;
    Node* tail;
  public:
    DoublyLinkedList();
    void tambahDepan(student);
    void tambahBelakang(student);
    void hapusDepan();
    void hapusBelakang();
};