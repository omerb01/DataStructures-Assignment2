//
// Created by Ilya on 6/8/2018.
//
#include "MinHeap.h"
#include <iostream>
#include <iomanip>
#include "exceptions.h"

using namespace std;

MinHeap::MinHeap(int n, int *array) {
    try {
        HeapArr = new Node *[2 * n];
        last = n;
        size = 2 * n;
        for (int i = 0; i < n; i++) {
            Node *new_node = new Node();
            new_node->index = new int();
            *(new_node->index) = i;
            new_node->data = array[i];
            if (2 * (i + 1) <= size) {
                new_node->left = 2 * (i + 1) - 1;
            } else {
                new_node->left = nullptr;
            }
            if ((2 * i + 2) < size) {
                new_node->right = 2 * (i + 1);
            } else {
                new_node->right = nullptr;
            }
            HeapArr[i] = new_node;
        }
        for (int i = n; i < 2 * n; i++) {
            HeapArr[i] = nullptr;
        }
        siftDown(last - 1, this);
    }catch(std::bad_alloc &ba){
        throw MinHeapBadAlloc();
    }
}

MinHeap::MinHeap(const MinHeap& heap){
    this->size=heap.size;
    this->last=heap.last;
    this->HeapArr = new Node*[size];
    for(int i=0;i<size;i++){
       this->HeapArr[i]=heap.HeapArr[i];
    }
}

MinHeap& MinHeap::operator=(const MinHeap& heap){
    this->deleteHeap();
    this->size=heap.size;
    this->last=heap.last;
    this->HeapArr = new Node*[heap.size];
    for(int i=0;i<heap.size;i++){
        this->HeapArr[i]=heap.HeapArr[i];
    }
}

int **MinHeap::getIndexes(int* sortedIDs) {
    int **indexes = new int *[size];
    int* sortedCIDs = new int[size];
    for (int i = 0; i < size; i++) {
        indexes[i] = HeapArr[i]->index;
        sortedCIDs[i]=HeapArr[i]->data;
    }
    return indexes;
}



bool MinHeap::isMin(Node *node, MinHeap *minHeap) {
    Node **MinHeapArr = minHeap->HeapArr;
    if ((node->right != nullptr && MinHeapArr[node->right] != nullptr) &&
        MinHeapArr[node->right]->data < node->data) {
        return false;
    }
    if ((node->left != nullptr && MinHeapArr[node->left] != nullptr) &&
        MinHeapArr[node->left]->data < node->data) {
        return false;
    }
    return true;
}

int MinHeap::getMin(Node *node, MinHeap *minHeap) {
    Node **MinHeapArr = minHeap->HeapArr;
    int min = node->data;
    if (MinHeapArr[node->right] != nullptr &&
        MinHeapArr[node->right]->data < min) {
        min = MinHeapArr[node->right]->data;
    }
    if (MinHeapArr[node->left] != nullptr &&
        MinHeapArr[node->left]->data < min) {
        min = MinHeapArr[node->left]->data;
    }
    return min;
}

void MinHeap::swap(Node *node, MinHeap *minHeap) {
    Node **MinHeapArr = minHeap->HeapArr;
    int min = getMin(node, minHeap);
    int temp, *temp_index, temp_index_value, temp2_index_value;
    if (node->right != nullptr && MinHeapArr[node->right] != nullptr &&
        MinHeapArr[node->right]->data == min) {
        temp = node->data;
        temp_index = node->index;
        temp_index_value = *(node->index);
        temp2_index_value = *(MinHeapArr[node->right]->index);
        node->data = MinHeapArr[node->right]->data;
        node->index = MinHeapArr[node->right]->index;
        *(node->index) = temp_index_value;
        MinHeapArr[node->right]->data = temp;
        MinHeapArr[node->right]->index = temp_index;
        *(MinHeapArr[node->right]->index) = temp2_index_value;
    } else if (node->left != nullptr && MinHeapArr[node->left] != nullptr &&
               MinHeapArr[node->left]->data == min) {
        temp = node->data;
        temp_index = node->index;
        temp_index_value = *(node->index);
        temp2_index_value = *(MinHeapArr[node->left]->index);
        node->data = MinHeapArr[node->left]->data;
        node->index = MinHeapArr[node->left]->index;
        *(node->index) = temp_index_value;
        MinHeapArr[node->left]->data = temp;
        MinHeapArr[node->left]->index = temp_index;
        *(MinHeapArr[node->left]->index) = temp2_index_value;
    }
}

void MinHeap::siftDown(int index, MinHeap *minHeap) {
    Node **MinHeapArr = minHeap->HeapArr;
    for (int i = ceil(index / 2.0); i >= 0; i--) {
        if (MinHeapArr[i]->left == nullptr &&
            MinHeapArr[i]->right == nullptr ||
            isMin(MinHeapArr[i], minHeap)) {
        } else {
            swap(MinHeapArr[i], minHeap);
        }
    }
    for (int i = 0; i <= ceil(index / 2.0); i++) {
        if (MinHeapArr[i]->left == nullptr &&
            MinHeapArr[i]->right == nullptr ||
            isMin(MinHeapArr[i], minHeap)) {
        } else {
            swap(MinHeapArr[i], minHeap);
        }
    }
}

void MinHeap::printArr() {
    for (int i = 0; i < last; i++) {
        cout << HeapArr[i]->data << endl;
    }
}

void MinHeap::deleteHeap(){
    for (int i = 0; i < last; i++) {
        if (HeapArr[i] != nullptr) {
            delete HeapArr[i];
        }
    }
    delete []HeapArr;
}

void MinHeap::expandArray(MinHeap *minHeap) {
    minHeap->size *= 2;
    Node **new_arr = new Node *[minHeap->size];
    int last = minHeap->last;
    int size = minHeap->size;
    for (int i = 0; i < minHeap->last; i++) {
        new_arr[i] = minHeap->HeapArr[i];
        if (new_arr[i]->left == 0 && (2*(i+1) <= size)) {
            new_arr[i]->left = 2 * (i + 1) - 1;
        } else if(new_arr[i]->left == 0){
            new_arr[i]->left = nullptr;
        }
        if (new_arr[i]->right == 0 &&(2 * (i + 1) + 1) < size) {
            new_arr[i]->right = 2 * (i + 1);
        } else if(new_arr[i]->right == 0) {
            new_arr[i]->right = nullptr;
        }
    }
    for (int i = minHeap->last; i < minHeap->size; i++) {
        new_arr[i] = nullptr;
    }
    if (minHeap->HeapArr != nullptr) delete minHeap->HeapArr;
    minHeap->HeapArr = new_arr;
}

void MinHeap::decreaseArray(MinHeap *minHeap) {
    try{
        minHeap->size /= 2;
        if (minHeap->size == 0) {
            return;
        }
        Node **new_arr = new Node *[minHeap->size];
        for (int i = 0; i < minHeap->last; i++) {
            new_arr[i] = minHeap->HeapArr[i];
        }
        for (int i = minHeap->last; i < minHeap->size; i++) {
            new_arr[i] = nullptr;
        }
        delete minHeap->HeapArr;
        minHeap->HeapArr = new_arr;
    }catch (std::bad_alloc &ex){
        throw MinHeapBadAlloc();
    }

}

int *MinHeap::insert(int data) {
    try{if (last + 1 >= size) {
            expandArray(this);
        }
        Node *new_node = new Node();
        new_node->data = data;
        new_node->index = new int();
        int *pointer_to_return = new_node->index;
        *(new_node->index) = last;
        new_node->index;
        if (last == 0 && size == 2) {
            new_node->left = 1;
            new_node->right = nullptr;
        } else {
            if (2 * (last + 1 + 1) <= size) {
                new_node->left = 2 * (last + 1 + 1) - 1;
            } else {
                new_node->left = nullptr;
            }
            if ((2 * (last + 1) + 2) < size) {
                new_node->right = 2 * (last + 1 + 1);
            } else {
                new_node->right = nullptr;
            }
        }
        HeapArr[last] = new_node;
        last++;
        siftDown(last - 1, this);
        return pointer_to_return;
    }catch(std::bad_alloc &ex){
        throw MinHeapBadAlloc();
    }

}

void MinHeap::decKey(int index, int new_data) {
    if (!(index >= 0 && index < last)) {
        return;
    }
    if (!(HeapArr[index]->data < new_data)) {
        HeapArr[index]->data = new_data;
        siftDown(index - 1, this);
    }
}

int MinHeap::findMin() {
    if (HeapArr[0] == nullptr) throw MinHeapElementNotFound();
    else return HeapArr[0]->data;
}

void MinHeap::delMin() {
    int temp = HeapArr[last - 1]->data;
    HeapArr[last - 1]->data = HeapArr[0]->data;
    HeapArr[0]->data = temp;
    delete HeapArr[last - 1];
    HeapArr[last - 1] = nullptr;
    last--;
    if (last == 0) {
        return;
    }
    siftDown(last - 1, this);
    if (size >= last * 4) {
        decreaseArray(this);
    }
}

void MinHeap::delNode(int index) {
    if (!(index >= 0 && index < last)) {
        return;
    }
    decKey(index, HeapArr[0]->data - 100);
    siftDown(last - 1, this);
    delMin();
}

MinHeap::~MinHeap() {
    deleteHeap();
}