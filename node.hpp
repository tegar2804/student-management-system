#pragma once

class Node {
public:
  student data;
  Node* left;
  Node* right;

  Node ();
  Node (student);
};