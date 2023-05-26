#pragma once

#include "node.hpp"
#include "myVector.hpp"

template <typename T>
class avl {
   private:
      Node<T> *root;
   public:
      avl();
      Node<T> *get_root();
      void update_root(Node<T> *);
      int height(Node<T> *);
      int difference(Node<T> *);
      Node<T> *rr_rotat(Node<T> *);
      Node<T> *ll_rotat(Node<T> *);
      Node<T> *lr_rotat(Node<T> *);
      Node<T> *rl_rotat(Node<T> *);
      Node<T> *balance(Node<T> *);
      Node<T> *insert(Node<T> *, T*);
      Node<T>* minValueNode(Node<T>*);
      Node<T>* deleteNode(Node<T>*, Node<T>*);
      Node<T> *searchNode(Node<T> *, std::string);
      myVector<T> *inorder(Node<T> *);
};