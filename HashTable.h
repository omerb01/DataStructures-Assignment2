//
// Created by Omer on 07/06/2018.
//

#ifndef DATASTRUCTURES_HW2_HASHTABLE_H
#define DATASTRUCTURES_HW2_HASHTABLE_H

#include <cmath>
#include "exceptions.h"

template<typename T>
class HashTable {

    struct Node {
        T *data;
        int key;
        Node *next;

        Node(T data, int key) {
            this->data = new T(data);
            this->key = key;
            next = nullptr;
        }
    };

    Node **table;
    int size;
    int num_of_elements;

    int hash(int key) {
        const double a = (sqrt(5) - 1) / 2;
        return (int) floor(size * modf(a * key, nullptr));
    }

    bool isLaden() {
        double load = num_of_elements / size;
        return load >= 1.0;
    }

    void rehash() {
        int old_size = size;
        Node **old_table = table;

        size = num_of_elements * 2;
        table = new Node *[size];
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
        }

        for (int i = 0; i < old_size; i++) {
            Node *old_list = old_table[i];
            while (old_list != nullptr) {
                Node *node = new Node(*old_list->data, old_list->key);

                int index = hash(old_list->key);
                if (table[index] != nullptr) {
                    Node *list = table[index];
                    node->next = list;
                }
                table[index] = node;

                old_list = old_list->next;
            }
        }

        deleteTable(old_table, old_size);
    }

    static void deleteTable(Node **table, int size) {
        for (int i = 0; i < size; i++) {
            Node* list = table[i];
            while(list != nullptr) {
                Node* next = list->next;
                delete list;
                list = next;
            }
        }

        delete[] table;
    }

public:

    HashTable(int num_of_initial_elements, T **elements, int *keys) {
        num_of_elements = num_of_initial_elements;
        size = num_of_initial_elements * 2;

        table = new Node *[size];
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
        }

        for (int i = 0; i < num_of_initial_elements; i++) {
            int index = hash(keys[i]);

            Node *node = new Node(*elements[i], keys[i]);
            if (table[index] != nullptr) {
                Node *list = table[index];
                node->next = list;
            }
            table[index] = node;
        }
    }

    ~HashTable() {
        deleteTable(table, size);
    }

    bool insert(T *data, int key) {
        int index = hash(key);

        Node *node = new Node(*data, key);
        if (table[index] != nullptr) {
            Node *list = table[index];
            while (list != nullptr) {
                if (list->key == key) return false;
                list = list->next;
            }
            node->next = table[index];
        }

        table[index] = node;
        num_of_elements++;

        if (isLaden()) rehash();
        return true;
    }

    T &search(int key) {
        int index = hash(key);
        Node *list = table[index];

        while (list != nullptr) {
            if (list->key == key) {
                return *list->data;
            }
            list = list->next;
        }

        throw HashElementNotFound();
    }

};

#endif //DATASTRUCTURES_HW2_HASHTABLE_H
