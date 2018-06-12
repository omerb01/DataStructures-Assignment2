//
// Created by Omer on 07/06/2018.
//

#ifndef DATASTRUCTURES_HW2_MINHEAP_H
#define DATASTRUCTURES_HW2_MINHEAP_H

#include "AVLTree.h"

class MinHeap {

    struct Node {
        int data;
        int right;
        int left;
        int *index;
    };
    Node **HeapArr=nullptr;
    int last=0,size=0;

    static void siftDown(int index, MinHeap *minHeap);
    static bool isMin(Node* node, MinHeap *minHeap);
    static void swap(Node* node, MinHeap *minHeap);
    static int getMin(Node *node, MinHeap *minHeap);
    static void expandArray(MinHeap *minHeap);
    static void decreaseArray(MinHeap *minHeap);
public:

    MinHeap() =default;

    MinHeap(int n, int* array);

    int** getIndexes();

    int* getSortedID();

    MinHeap(const MinHeap& heap);

    MinHeap& operator=(const MinHeap& heap);

    int* insert(int data);

    void decKey(int index, int new_data);

    int findMin();

    void delNode(int index);

    void delMin();

    //TODO: temp
    void printArr();

    void deleteHeap();

    ~MinHeap();
};

#endif //DATASTRUCTURES_HW2_MINHEAP_H
