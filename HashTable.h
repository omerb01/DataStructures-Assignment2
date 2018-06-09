//
// Created by Omer on 07/06/2018.
//

#ifndef DATASTRUCTURES_HW2_HASHTABLE_H
#define DATASTRUCTURES_HW2_HASHTABLE_H

#include <cmath>

template<typename T>
class HashTable {

    class HashFunction {
        int m;
        const double a = (sqrt(5) - 1) / 2;

    public:

        HashFunction(int m);

        void expandM();

        int operator()(int key);
    };

    HashFunction func;
    T *table;
    int size;
    int num_of_elements;

    void rehash();

public:

    HashTable(int num_of_initial_elements);

    void insert(T data, int key);

    T &search(int key);

};

#endif //DATASTRUCTURES_HW2_HASHTABLE_H
