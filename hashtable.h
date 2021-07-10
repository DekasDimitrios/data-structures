#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "database.h"
#include "item.h"

template <class T> class hashtable : public database<T> {
  public:
    hashtable(); // constructor
    void remove(int value) override; // removing asking value
    int hash(int key); // finding needed location to store the given value while given only the value ( key % HashTable Size )
    int hash(int, int); // finding needed location to store the given value while given the value plus the doubled sized of the HashTable
    int idFounder(int id); // finds the location that the given ID has been stored
    void insert(T value) override; // inserts the given value
    void reSize(); // resizing the HashTable so that it can store double the size that it did
    T *find(int id) override; // returns T* using idFounder in order to find the location of the given ID inside the HashTable
    std::vector<T> return_all() override; // Returns all the content of HashTable
    int currentValues = 0; // Initializing CurrentValues that the HashTable stores at 0

  private:
    std::vector< item<T> > HashTable;
};

template <class T> hashtable<T>::hashtable() {
    for (int i = 0; i < 20; i++) {
        item<T> it;
        HashTable.push_back(it);
    }
}

template <class T> std::vector<T> hashtable<T>::return_all() {
    std::vector<T> res;
    for (int i = 0; i < HashTable.size(); i++) {
        item<T> *ptr = &HashTable[i];
        if ((int)ptr->data != -1 && !HashTable[i].deleted) {
            res.push_back(ptr->data);
        }
    }
    return res;
}

template <class T> int hashtable<T>::hash(int key) {
    return key % (int)HashTable.size();
}

template <class T> int hashtable<T>::hash(int key, int n) {
    return key % n;
}

template <class T> int hashtable<T>::idFounder(int id) {

   while ((int)HashTable[hash(id)].data != -1) {
        if (HashTable[hash(id)].data == id) {
            return hash(id);
        } else {
            id++;
            if (id == HashTable.size()) {
                id = 0;
            }
        }
    }
    return -1;
}

template <class T> T *hashtable<T>::find(int id) {
    int found_id = idFounder(id);
    if (found_id == -1 || HashTable[found_id].deleted) {
        return nullptr;
    } else {
        return &HashTable[found_id].data;
    }
}
template <class T> void hashtable<T>::insert(T value) {
    int index = hash((int)value);

    while (HashTable[index].data != -1 && HashTable[index].data != value) {

        index++;
        if (index > HashTable.size()) {
            index = 0;
        }
    }

    if (HashTable[index].data == value) {
        if (HashTable[index].deleted) {
            HashTable[index].deleted = false;
            currentValues++;
        }
    }

    if (HashTable[index].data == -1) {

        item<T> newit;
        newit.data = value;
        HashTable[index] = newit;
        currentValues++;
    }

    if (currentValues >= HashTable.size() / 2) {
        reSize();
    }
}

template <class T> void hashtable<T>::reSize() {
    clock_t a = clock();
    item<T> empty;
    std::vector< item<T> > resize(HashTable.size() * 2, empty);

    for (int i = 0; i < HashTable.size(); i++) {

        if ((int)HashTable[i].data != -1 && !HashTable[i].deleted) {
            int index = hash((int)HashTable[i].data, HashTable.size() * 2);
            while ((int)resize[index].data != -1) {
                index++;
                if (index == HashTable.size() * 2) {
                    index = 0;
                }
            }

            resize[index] = HashTable[i];
        }
    }
    
    HashTable = resize;
    clock_t b = clock();   
}

template <class T> void hashtable<T>::remove(int value) {

    int id_found = idFounder(value);
    if (id_found != -1) {

        if (HashTable[id_found].data == -1) {
        } else if ((int)HashTable[id_found].data == value) {
            HashTable[id_found].deleted = true;
            currentValues--;
        } else {
           
        }
    }

    return;
}

#endif