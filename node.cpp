#include <iostream>
#include "node.hpp"

template <typename T>
Node<T>::Node(){
    left = nullptr;
    right = nullptr;
}

template <typename T>
Node<T>::Node(T* data) {
  this->data = data;
  left = nullptr;
  right = nullptr;
}

template class Node<mahasiswa>;
template class Node<dosen>;
template class Node<matkul>;
template class Node<transkrip>;
