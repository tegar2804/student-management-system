#pragma once

#include "node.hpp"

class avl_tree {
   private:
      Node *root;
   public:
      int height(Node *);
      int difference(Node *);
      Node *rr_rotat(Node *);
      Node *ll_rotat(Node *);
      Node *lr_rotat(Node *);
      Node *rl_rotat(Node *);
      Node *balance(Node *);
      Node *insert(Node *, int);
      void inorder(Node *);
      void preorder(Node *);
      void postorder(Node*);
      avl_tree();
};