#ifndef AVLNODE_H
#define AVLNODE_H

#include "avltree.h"
#include <iostream>
template <class T> class AVLNode {
  public:
    AVLNode();
    AVLNode(T* element);
    T *nodedata; // Id and Neighbors
    AVLNode<T> *left; // Left Child
    AVLNode<T> *right; // Right Child
    AVLNode<T> *parent; // Parent of the node
    int balance; // Balance of the node
};

template<class T> AVLNode<T>::AVLNode() {
    nodedata = nullptr;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    balance = 0;
}

template <class T> AVLNode<T>::AVLNode(T* element) {
    nodedata = element;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    balance = 0;
}
#endif // AVLNODE_H
