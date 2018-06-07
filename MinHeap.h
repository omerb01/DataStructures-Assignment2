//
// Created by Omer on 07/06/2018.
//

#ifndef DATASTRUCTURES_HW2_MINHEAP_H
#define DATASTRUCTURES_HW2_MINHEAP_H

class MinHeap {

    struct Node {
        int data;
        Node *right;
        Node *left;
    };

    Node *root;

public:

    MinHeap(int n, int* array);

    MinHeap(const MinHeap& heap) = delete;

    MinHeap& operator=(const MinHeap& heap) = delete;

    void insert(int data);

    void decKey(int data, int x);

    int findMin();

    void delMin();
};

#endif //DATASTRUCTURES_HW2_MINHEAP_H
