#ifndef DATABASE_H
#define DATABASE_H
#include <vector>

/*
 * Virtual interface for every data structure we use.
 */
template <class T> class database {
  public:
    virtual void insert(T) {}
    virtual void remove(int) {}
    virtual T *find(int) { return NULL; }
    virtual std::vector<T> return_all() { return std::vector<T>(); }
};

#endif