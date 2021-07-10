#ifndef AVLTREE_H
#define AVLTREE_H

#include "avlnode.h"
#include "database.h"
#include <algorithm>
#include <iostream>

template <class T> class AVLTree : public database<T> {
  private:
    AVLNode<T> *root;
    int height(AVLNode<T> *node);      // Returns the height of the node
    void setBalance(AVLNode<T> *node); // Sets the balance factor of the node
    void reBalance(AVLNode<T> *node);  // Re balances the tree
    AVLNode<T> *
    node_find(int element); // Search for node in the AVLTree and return a
                            // pointer that leads to the node
    // Rotations
    AVLNode<T> *leftRotation(AVLNode<T> *node);
    AVLNode<T> *rightRotation(AVLNode<T> *node);
    AVLNode<T> *leftRightRotation(AVLNode<T> *node);
    AVLNode<T> *rightLeftRotation(AVLNode<T> *node);

  public:
    AVLNode<T> *getRoot() { return root; }
    std::vector<T> res;
    AVLTree() {
    
        root = nullptr;
    }                                // Create an empty AVLTree
    void insert(T element) override; // Insert T element in the starting AVL
    void remove(
        int element) override; // Find the corresponding element and delete it
    T *find(int element)
        override; // Use find_node and return the node's data or a nullptr
    void
    inOrder(AVLNode<T> *node); // Print the tree elements in order recursively
    std::vector<T> return_all() override;
};

// Find utility
template <class T> T *AVLTree<T>::find(int element) {
    AVLNode<T> *data = node_find(element);

    if (data == nullptr) {
        return nullptr;
    } else {
        return data->nodedata;
    }
}

template <class T> AVLNode<T> *AVLTree<T>::node_find(int element) {
    AVLNode<T> *elementPtr = root;
    while (elementPtr) {
        if (element < (int)(*elementPtr->nodedata))
            elementPtr = elementPtr->left;
        else if (element > (int)(*elementPtr->nodedata))
            elementPtr = elementPtr->right;
        else
            return elementPtr;
    }
    return nullptr;
}

// Insert utility
template <class T> int AVLTree<T>::height(AVLNode<T> *node) {
    if (node == nullptr) {
        return -1; // -1 so leaves have 0 height
    }
    return 1 + std::max(height(node->left), height(node->right));
}
template <class T> void AVLTree<T>::setBalance(AVLNode<T> *node) {
    node->balance = height(node->right) - height(node->left);
}
template <class T> void AVLTree<T>::reBalance(AVLNode<T> *node) {
    setBalance(node);
    if (node->balance == -2) { // Left subtree causes the imbalance
        if (height(node->left->left) >= height(node->left->right)) {
            node = rightRotation(node);
            return;
        } else {
            node = leftRightRotation(node);
            return;
        }
    } else if (node->balance == 2) { // Right subtree causes the imbalance
        if (height(node->right->right) >= height(node->right->left)) {
            node = leftRotation(node);
            return;
        } else {
            node = rightLeftRotation(node);
            return;
        }
    }
    if (node->parent == nullptr) { // Only node without a parent is the root
        root = node;
    } else if (node->parent->balance != -2 &&
               node->parent->balance !=
                   2) { // Recurse until we reach the root while being balanced
        reBalance(node->parent);
    }
}
template <class T> void AVLTree<T>::insert(T element) {
    T *el = new T(element);
    AVLNode<T> *node = new AVLNode<T>(el); // create node
    if (root == nullptr) { // If our tree is empty the new node becomes our root
        root = node;
    } else { // Start from the root
        AVLNode<T> *node1 = root;
        AVLNode<T> *parent;

        while (true) { // Go down the tree until break
            if ((int)(*node1->nodedata) == (int)element) {
                return;
            } // If the element is already in the tree, return
            parent = node1;
            bool Left = (int)(*node1->nodedata) >
                        element; // Do we insert on left or right subtree?
            node1 = Left ? node1->left : node1->right;
            if (node1 == nullptr) { // If an empty spot is found, insert
                if (Left) {         // Go left
                    parent->left = node;
                    parent->left->parent = parent;

                } else { // Go right
                    parent->right = node;
                    parent->right->parent = parent;
                }
                reBalance(parent);
                break;
            }
        }
    }
    return;
}

// Remove utility
template <class T> void AVLTree<T>::remove(int element) {
    clock_t c = clock();
    if (root == nullptr) // Nothing to remove from an empty tree
        return;
    AVLNode<T> *node = root;
    AVLNode<T> *parent = root;
    AVLNode<T> *delNode = nullptr;
    AVLNode<T> *child = root;
    while (child !=
           nullptr) { // Stop the searching process when child becomes null
        parent = node;
        node = child;
        child = element >= (int)(*node->nodedata) ? node->right : node->left;
        if (element ==
            (int)(*node->nodedata)) { // Found the node we wish to remove
            delNode = node;
        }
    }
    if (delNode != nullptr) { // Did we find the node we wist to remove?
        delNode->nodedata = node->nodedata;
        child = node->left != nullptr ? node->left : node->right;
        if ((int)(*root->nodedata) ==
            element) {    // If we want to delete the root
            root = child; // the child becomes the root
        } else {          // Put the child in the right place
            if (parent->left == node) {
                parent->left = child;
            } else {
                parent->right = child;
            }
            reBalance(parent); // Re balance after remove
        }
    }

}

// Rotations
template <class T> AVLNode<T> *AVLTree<T>::leftRotation(AVLNode<T> *node) {
    AVLNode<T> *temp = node->right;
    temp->parent = node->parent;
    node->right = temp->left;
    if (node->right != nullptr) {
        node->right->parent = node;
    }
    temp->left = node;
    node->parent = temp;
    if (temp->parent != nullptr) {
        if (temp->parent->right == node) {
            temp->parent->right = temp;
        } else {
            temp->parent->left = temp;
        }
    }
    setBalance(node);
    setBalance(temp);
    return temp;
}
template <class T> AVLNode<T> *AVLTree<T>::rightRotation(AVLNode<T> *node) {
    AVLNode<T> *temp = node->left;
    temp->parent = node->parent;
    node->left = temp->right;
    if (node->left != nullptr) {
        node->left->parent = node;
    }
    temp->right = node;
    node->parent = temp;
    if (temp->parent != nullptr) {
        if (temp->parent->right == node) {
            temp->parent->right = temp;
        } else {
            temp->parent->left = temp;
        }
    }
    setBalance(node);
    setBalance(temp);
    return temp;
}
template <class T> AVLNode<T> *AVLTree<T>::leftRightRotation(AVLNode<T> *node) {
    node->left = leftRotation(node->left);
    return rightRotation(node);
}
template <class T> AVLNode<T> *AVLTree<T>::rightLeftRotation(AVLNode<T> *node) {
    node->right = rightRotation(node->right);
    return leftRotation(node);
}

// Output utility
template <class T> void AVLTree<T>::inOrder(AVLNode<T> *node) {
    if (node == nullptr) {
        return;
    } else {
        inOrder(node->left);
        res.push_back((int)(*node->nodedata));
        inOrder(node->right);
    }
}

template <class T> std::vector<T> AVLTree<T>::return_all() {
    res.clear();
    inOrder(getRoot());
    return res;
}

#endif
