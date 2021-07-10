#ifndef ITEM_H
#define ITEM_H
template <class T>
class item { // needed struct for the hash values version 1.01
  public:
    item() {
        data = -1;
        deleted=false;
    }
    T data;
    bool deleted;
};
#endif