#include "avl.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

avl_tree::avl_tree(){
   root = NULL;
}

int avl_tree::height(struct node *t) {
    int h = 0;
    if (t != NULL) {
        int l_height = height(t->left);
        int r_height = height(t->right);
        int max_height;
        if(l_height > r_height)
            max_height = l_height;
        else
            max_height = r_height;
        h = max_height + 1;
    }
    return h;
}

int avl_tree::difference(struct node *t) {
   int l_height = height(t->left);
   int r_height = height(t->right);
   int b_factor = l_height - r_height;
   return b_factor;
}

struct node *avl_tree::rr_rotat(struct node *parent) {
   struct node *t;
   t = parent->right;
   parent->right = t->left;
   t->left = parent;
   return t;
}

struct node *avl_tree::ll_rotat(struct node *parent) {
   struct node *t;
   t = parent->left;
   parent->left = t->right;
   t->right = parent;
   return t;
}

struct node *avl_tree::lr_rotat(struct node *parent) {
   struct node *t;
   t = parent->left;
   parent->left = rr_rotat(t);
   return ll_rotat(parent);
}

struct node *avl_tree::rl_rotat(struct node *parent) {
   struct node *t;
   t = parent->right;
   parent->right = ll_rotat(t);
   return rr_rotat(parent);
}

struct node *avl_tree::balance(struct node *t) {
   int bal_factor = difference(t);
   if (bal_factor > 1) {
      if (difference(t->left) > 0)
         t = ll_rotat(t);
      else
         t = lr_rotat(t);
   } else if (bal_factor < -1) {
      if (difference(t->right) > 0)
         t = rl_rotat(t);
      else
         t = rr_rotat(t);
   }
   return t;
}

struct node *avl_tree::insert(struct node *r, int v) {
   if (r == NULL) {
      r = new struct node;
      r->val = v;
      r->left = NULL;
      r->right = NULL;
      return r;
   } else if (v < r->val) {
      r->left = insert(r->left, v);
      r = balance(r);
   } else if (v >= r->val) {
      r->right = insert(r->right, v);
      r = balance(r);
   } return r;
}

void avl_tree::inorder(struct node *t) {
   if (t == NULL)
      return;
      inorder(t->left);
      cout << t->val << " ";
      inorder(t->right);
}

void avl_tree::preorder(struct node *t) {
   if (t == NULL)
      return;
      cout << t->val << " ";
      preorder(t->left);
      preorder(t->right);
}

void avl_tree::postorder(struct node *t) {
   if (t == NULL)
      return;
      postorder(t ->left);
      postorder(t ->right);
      cout << t->val << " ";
}