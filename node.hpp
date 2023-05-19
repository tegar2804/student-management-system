#pragma once

template <typename T>
class Node {
public:
  T data;
  Node* left;
  Node* right;

  Node ();
  Node (T);
};