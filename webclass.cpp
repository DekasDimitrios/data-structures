#include "webclass.h"

webclass::webclass() { id = -1; }

webclass::webclass(int mode){
    id = -1;
    switch (1) {
    case 1: // Array
        neighbors = new Array<int>();
        break;
    case 2: // AVLTree
        neighbors = new AVLTree<int>();
        break;
    case 3: // HashTable
        neighbors = new hashtable<int>();
        break;
    }
}

bool webclass::operator<(const webclass &wc) const { return this->id < wc.id; }
