//
// Created by Ilya on 6/8/2018.
//
#include "MinHeap.h"
#include <iostream>
#include <iomanip>

using namespace std;

MinHeap::MinHeap(int n, int *array) {
    if (n < 2 || array == nullptr) {
        HeapArr = nullptr;
    } else {
        HeapArr = new Node *[2*n];
        last = n;
        size=2*n;
        for (int i = 0; i < n; i++) {
            Node *new_node = new Node();
            if (new_node == nullptr) {
                //TODO:take care
            }
            new_node->data = array[i];
            if (2 * (i+1) <= size) {
                new_node->left = 2 * (i+1)-1;
            } else {
                new_node->left = nullptr;
            }
            if ((2 * i + 2) < size) {
                new_node->right = 2 * (i+1);
            } else {
                new_node->right = nullptr;
            }
            HeapArr[i] = new_node;
        }
        for(int i=n;i<2*n;i++){
            HeapArr[i]=nullptr;
        }
    }
    siftDown(last - 1, this);
}

bool MinHeap::isMin(Node *node, MinHeap *minHeap) {
    Node **MinHeapArr = minHeap->HeapArr;
    if ((node->right != nullptr && MinHeapArr[node->right] != nullptr) &&
        MinHeapArr[node->right]->data < node->data) {
        return false;
    }
    if ((node->left != nullptr && MinHeapArr[node->left] != nullptr)&&
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
    int temp;
    if (node->right != nullptr && MinHeapArr[node->right] != nullptr  && MinHeapArr[node->right]->data == min) {
        temp = node->data;
        node->data = MinHeapArr[node->right]->data;
        MinHeapArr[node->right]->data = temp;
    } else if (node->left != nullptr && MinHeapArr[node->left] != nullptr  && MinHeapArr[node->left]->data == min) {
        temp = node->data;
        node->data = MinHeapArr[node->left]->data;
        MinHeapArr[node->left]->data = temp;
    }
}

void MinHeap::siftDown(int index, MinHeap *minHeap) {
    Node **MinHeapArr = minHeap->HeapArr;
    for (int i=ceil(index/2.0); i >= 0; i--) {
        if (MinHeapArr[i]->left == nullptr &&
            MinHeapArr[i]->right == nullptr ||
            isMin(MinHeapArr[i], minHeap)) {
        } else {
            swap(MinHeapArr[i], minHeap);
        }
    }
    for (int i=0; i <=ceil(index/2.0) ; i++) {
        if (MinHeapArr[i]->left == nullptr &&
            MinHeapArr[i]->right == nullptr ||
            isMin(MinHeapArr[i], minHeap)) {
        } else {
            swap(MinHeapArr[i], minHeap);
        }
    }
}

void MinHeap::printArr() {
    for(int i=0;i<last;i++){
        cout<<HeapArr[i]->data<<endl;
    }
}


void MinHeap::expandArray(MinHeap *minHeap){
    minHeap->size*=2;
    Node** new_arr = new Node *[minHeap->size];
    for(int i=0;i<minHeap->last;i++){
        new_arr[i]=minHeap->HeapArr[i];
    }
    for(int i=minHeap->last;i<minHeap->size;i++){
        new_arr[i]= nullptr;
    }
    delete minHeap->HeapArr;
    minHeap->HeapArr=new_arr;
}

void MinHeap::decreaseArray(MinHeap *minHeap){
    minHeap->size/=2;
    Node** new_arr = new Node *[minHeap->size];
    for(int i=0;i<minHeap->last;i++){
        new_arr[i]=minHeap->HeapArr[i];
    }
    for(int i=minHeap->last;i<minHeap->size;i++){
        new_arr[i]= nullptr;
    }
    delete minHeap->HeapArr;
    minHeap->HeapArr=new_arr;
}

void MinHeap::insert(int data){
    if(last+1 == size){
        expandArray(this);
    }
    //TODO: if node is already in system, HashTable should take care of it with better time complexity
    Node* new_node=new Node();
    new_node->data=data;
    if (2 * (last+1+1) <= size) {
        new_node->left = 2 * (last+1+1)-1;
    } else {
        new_node->left = nullptr;
    }
    if ((2 * (last+1) + 2) < size) {
        new_node->right = 2 * (last+1+1);
    } else {
        new_node->right = nullptr;
    }
    HeapArr[last]=new_node;
    last++;
    siftDown(last-1,this);
}

void MinHeap::decKey(int index,int new_data){
    if(!(index >= 0 && index<=last)){
        return;
    }
    if(!(HeapArr[index]->data<new_data)){
        HeapArr[index]->data=new_data;
        siftDown(index-1,this);
    }
}

int MinHeap::findMin(){
    return HeapArr[0]->data;
}

void MinHeap::delMin() {
    int temp = HeapArr[last - 1]->data;
    HeapArr[last - 1]->data = HeapArr[0]->data;
    HeapArr[0]->data = temp;
    delete HeapArr[last-1];
    HeapArr[last-1]=nullptr;
    last--;
    if(last==0){
        return;
    }
    siftDown(last-1,this);
    if(size>=last*4){
        decreaseArray(this);
    }
}

void MinHeap::delNode(int index) {
    if(!(index >= 0 && index<=last)){
        return;
    }
    decKey(index,HeapArr[0]->data-100);
    siftDown(last-1,this);
    delMin();
}

MinHeap::~MinHeap() {
    for (int i = 0; i < last; i++) {
        if (HeapArr[i] != nullptr) {
            delete HeapArr[i];
        }
    }
    delete HeapArr;
}