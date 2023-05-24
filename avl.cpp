#include "avl.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

template <typename T>
avl<T>::avl(){
   root = nullptr;
}

template <typename T>
Node<T> *avl<T>::get_root(){
   return root;
}

template <typename T>
void avl<T>::update_root(Node<T> *newRoot){
   root = newRoot;
}

template <typename T>
int avl<T>::height(Node<T> *t) {
    int h = 0;
    if (t != nullptr) {
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

template <typename T>
int avl<T>::difference(Node<T> *t) {
   int l_height = height(t->left);
   int r_height = height(t->right);
   int b_factor = l_height - r_height;
   return b_factor;
}

template <typename T>
Node<T> *avl<T>::rr_rotat(Node<T> *parent) {
   Node<T> *t;
   t = parent->right;
   parent->right = t->left;
   t->left = parent;
   return t;
}

template <typename T>
Node<T> *avl<T>::ll_rotat(Node<T> *parent) {
   Node<T> *t;
   t = parent->left;
   parent->left = t->right;
   t->right = parent;
   return t;
}

template <typename T>
Node<T> *avl<T>::lr_rotat(Node<T> *parent) {
   Node<T> *t;
   t = parent->left;
   parent->left = rr_rotat(t);
   return ll_rotat(parent);
}

template <typename T>
Node<T> *avl<T>::rl_rotat(Node<T> *parent) {
   Node<T> *t;
   t = parent->right;
   parent->right = ll_rotat(t);
   return rr_rotat(parent);
}

template <typename T>
Node<T> *avl<T>::balance(Node<T> *t) {
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

template <typename T>
Node<T> *avl<T>::insert(Node<T> *r, T *input) {
   if (r == nullptr) {
      Node<T> *r = new Node<T>(input);
      return r;
   } else if (input->getId() < r->data->getId()) {
      r->left = insert(r->left, input);
      r = balance(r);
   } else if (input->getId() >= r->data->getId()) {
      r->right = insert(r->right, input);
      r = balance(r);
   } 
   return r;
}

template <typename T>
Node<T> *avl<T>::searchNode(Node<T>* node, string id) {
    if (node == nullptr || node->data->getId() == id)
        return node;
    if (id < node->data->getId())
        return searchNode(node->left, id);

    return searchNode(node->right, id);
}

template <typename T>
myVector<T> *avl<T>::inorder(Node<T> *t) {
   myVector<T> *ans = new myVector<T>();

   if (t == nullptr) return ans;

   myVector<T> *left_ch = inorder(t->left);
   for(int i = 0; i < left_ch->size(); i++){
      ans->push(left_ch->get(i));
   }
   
   ans->push(t->data);

   myVector<T> *right_ch = inorder(t->right);
   for(int i = 0; i < right_ch->size(); i++){
      ans->push(right_ch->get(i));
   }

   return ans;
}

template <typename T>
Node<T>* avl<T>::minValueNode(Node<T>* node) {
   Node<T>* current = node;
   
   while (current && current->left != nullptr) {
      current = current->left;
   }
   
   return current;
}

template <typename T>
Node<T>* avl<T>::deleteNode(Node<T>* r, Node<T>* value) {
   if (r == nullptr) {
      return r;
   }
    
   if (value->data->getId() < r->data->getId()) {
      r->left = deleteNode(r->left, value);
      r = balance(r);
   } else if (value->data->getId() > r->data->getId()) {
      r->right = deleteNode(r->right, value);
      r = balance(r);
   } else {
      if (r->left == nullptr || r->right == nullptr) {
         Node<T>* temp = r->left ? r->left : r->right;
         
         if (temp == nullptr) {
            temp = r;
            r = nullptr;
         } else {
            *r = *temp;
         }
         
         delete temp;
      }
      else {
         Node<T>* temp = minValueNode(r->right);
         r->data = temp->data;
         r->right = deleteNode(r->right, temp);
         r = balance(r);
      }
   }
   
   return r;
}


template class avl<dosen>;
template class avl<matkul>;
template class avl<mahasiswa>;