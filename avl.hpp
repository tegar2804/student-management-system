#pragma once

#include "node.hpp"

class avl_tree {
   private:
      struct node *root;
   public:
      int height(struct node *);
      int difference(struct node *);
      struct node *rr_rotat(struct node *);
      struct node *ll_rotat(struct node *);
      struct node *lr_rotat(struct node*);
      struct node *rl_rotat(struct node *);
      struct node * balance(struct node *);
      struct node * insert(struct node*, int);
      void inorder(struct node *);
      void preorder(struct node *);
      void postorder(struct node*);
      avl_tree();
};