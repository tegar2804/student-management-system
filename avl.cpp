#include "avl.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

avl_tree::avl_tree(){
   root = NULL;
}

int avl_tree::height(Node *t) {
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

int avl_tree::difference(Node *t) {
   int l_height = height(t->left);
   int r_height = height(t->right);
   int b_factor = l_height - r_height;
   return b_factor;
}

Node *avl_tree::rr_rotat(Node *parent) {
   Node *t;
   t = parent->right;
   parent->right = t->left;
   t->left = parent;
   return t;
}

Node *avl_tree::ll_rotat(Node *parent) {
   Node *t;
   t = parent->left;
   parent->left = t->right;
   t->right = parent;
   return t;
}

Node *avl_tree::lr_rotat(Node *parent) {
   Node *t;
   t = parent->left;
   parent->left = rr_rotat(t);
   return ll_rotat(parent);
}

Node *avl_tree::rl_rotat(Node *parent) {
   Node *t;
   t = parent->right;
   parent->right = ll_rotat(t);
   return rr_rotat(parent);
}

Node *avl_tree::balance(Node *t) {
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

Node *avl_tree::insert(Node *r, int v) {
   if (r == NULL) {
      r = new Node;
      r->data = v;
      r->left = NULL;
      r->right = NULL;
      return r;
   } else if (v < r->data) {
      r->left = insert(r->left, v);
      r = balance(r);
   } else if (v >= r->data) {
      r->right = insert(r->right, v);
      r = balance(r);
   } return r;
}

void avl_tree::inorder(Node *t) {
   if (t == NULL)
      return;
      inorder(t->left);
      cout << t->data << " ";
      inorder(t->right);
}

void avl_tree::preorder(Node *t) {
   if (t == NULL)
      return;
      cout << t->data << " ";
      preorder(t->left);
      preorder(t->right);
}

void avl_tree::postorder(Node *t) {
   if (t == NULL)
      return;
      postorder(t ->left);
      postorder(t ->right);
      cout << t->data << " ";
}