#ifndef ARRAY_H
#define ARRAY_H
#include "database.h"
#include <algorithm>
#include <vector>
template <class T> class Array : public database<T> {
  private:
    T *binary_search(int); // binary search to find the T of an int key
    std::vector<T> data_items; // the main data storage
    int find_index_of(int item); //uses binary search to find the index of an int key
  public:
    Array();
    void insert(T) override; //Inserts T at the sorted position
    void remove(int) override; //Removes the specific int key
    T *find(int) override; // returns the pointer of the T value according to the int key
    std::vector<T> return_all() override; //returns all the data
};

template <class T> Array<T>::Array() {}

/*
* Same as find_index_of except it returns the T*
*/
template <class T> T *Array<T>::binary_search(int key) {
    size_t mid, left = 0;
    size_t right = data_items.size();
    while (left < right) {
        mid = left + (right - left) / 2;
        if (key > data_items[mid]) {
            left = mid + 1;
        } else if (key < data_items[mid]) {
            right = mid;
        } else {
            return &data_items[mid];
        }
    }

    return nullptr; // In case it's not found
}

template <class T> int Array<T>::find_index_of(int key) {
    size_t mid, left = 0;
    size_t right = data_items.size();
    while (left < right) {
        mid = left + (right - left) / 2;
        if (key > data_items[mid]) {
            left = mid + 1;
        } else if (key < data_items[mid]) {
            right = mid;
        } else {
            return mid;
        }
    }
    return -1; // In case it's not found
}

//virtual function
template <class T> T *Array<T>::find(int item) { return binary_search(item); }

template <class T> void Array<T>::insert(T a) {
    if(find((int)a) != nullptr) {
        return;
    }
    auto it = std::upper_bound(data_items.begin(), data_items.end(), a); //find by comparison the biggest value inside the storage.
    data_items.insert(it, a); //Insert after so it is sorted
}

template <class T> void Array<T>::remove(int id) {
    int index = find_index_of(id); // find the index using binary search
    if (index != -1) // If it is found erase it.
        data_items.erase(data_items.begin() + index);
}

template <class T> std::vector<T> Array<T>::return_all() { return data_items; }
#endif
