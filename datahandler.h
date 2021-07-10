#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "array.h"
#include "avltree.h"

#include "webclass.h"
#include "hashtable.h"

class datahandler {
  private:
    int mode;

  public:
    int max_id;
    database<webclass> *data;
    datahandler(int mode); // 1 = Array | 2 = AVL_Tree | 3 = Hash_Table
    void insert(int id, int neighbor); // adds a new neighbor to a specific id.
                                       // TODO:
                                       // AVLTree<int> get(int id);
                                       // HashTable<int> get(int id);
    void remove(int id, int neighbor);
    std::vector<int> findNeighbors(int id);
    Array<webclass> dfs(); // It creates the appropriate graph and uses DFS class to return the component.
    // Getters & Setters
    void setMode(int mode) { this->mode = mode; }
    int getMode() { return this->mode; }
};

#endif