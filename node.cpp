#include <iostream>
#include "node.hpp"

template <typename T>
Node<T>::Node(){
    left = NULL;
    right = NULL;
}

template <typename T>
Node<T>::Node(T data) {
  this->data = data;
  left = NULL;
  right = NULL;
}

template class Node<mahasiswa>;