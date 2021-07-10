#ifndef WEBCLASS_H
#define WEBCLASS_H
#include "array.h"
#include "avltree.h"
#include "database.h"
#include "hashtable.h"
class webclass {
  public:
    webclass();
    webclass(int mode);
    int id = -1;
    database<int> *neighbors;

    bool operator==(int rhs) {
        if (rhs == id) {
            return true;
        }
        return false;
    }

    webclass &operator=(int rhs) {
        this->id = rhs;

        return *this;
    }
    operator int() const { return this->id; }
    bool operator<(const webclass &) const;
};

#endif