#include <iostream>
#include "node.hpp"
#include "model.hpp"

Node::Node(){
    left = NULL;
    right = NULL;
}

Node::Node(student data) {
  this->data = data;
  left = NULL;
  right = NULL;
}