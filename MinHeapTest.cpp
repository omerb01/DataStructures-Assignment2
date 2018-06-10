//
// Created by Ilya on 6/8/2018.
//

#include "exceptions.h"
#include "MinHeap.h"
#include <iostream>
#include <cstdlib>
#include "HashTable.h"
#include "testMacros.h"


using namespace std;


bool getIndexes() {
    int arr[7]={5,-6,2,-4,100,55,-55};
    MinHeap heap(7,arr);
    int** indexes=heap.getIndexes();
    for(int i=0;i<7;i++){
        if(i != *indexes[i]) return false;
    }
    return true;
}

bool insert(){
    int arr[7]={5,-6,2,-4,100,55,-55};
    MinHeap heap(7,arr);
    heap.insert(-5);
    int** indexes=heap.getIndexes();
    if(*indexes[7]!=7) return false;
    heap.insert(-56);
    heap.insert(1);
    return true;
}

bool getMin(){
    int arr[7]={5,-6,2,-4,100,55,-55};
    MinHeap heap(7,arr);
    heap.delMin();
    if(heap.findMin() != -6) return false;
    heap.delMin();
    if(heap.findMin() != -4) return false;
    heap.insert(-55);
    heap.delMin();
    if(heap.findMin() != -4) return false;
    heap.delMin();
    if(heap.findMin() != 2) return false;
    heap.delMin();
    if(heap.findMin() != 5) return false;
    heap.delMin();
    if(heap.findMin() != 55) return false;
    heap.delMin();
    if(heap.findMin() != 100) return false;
    heap.delMin();
    heap.findMin();
    if(heap.findMin() != 0) return false;
    return true;
}

bool decKey(){
    int arr[7]={5,-6,2,-4,100,55,-55};
    MinHeap heap(7,arr);
    heap.decKey(6,-45);
    if(heap.findMin() != -55) return false;
    heap.decKey(6,-56);
    if(heap.findMin() != -56) return false;
    heap.decKey(0,-100);
    heap.decKey(1,-10);
    heap.decKey(2,-20);
    heap.decKey(3,-30);
    heap.decKey(4,-40);
    heap.decKey(5,-50);
    heap.decKey(6,-60);
    //ALL NODES SHOULD BE NEGATIVE
    heap.printArr();
    return true;
}

bool delNode(){
    int arr[7]={5,-6,2,-4,100,55,-55};
    MinHeap heap(7,arr);
    heap.delNode(6);
    if(heap.findMin() != -55) return false;
    heap.delNode(5);
    if(heap.findMin() != -55) return false;
    heap.delNode(4);
    if(heap.findMin() != -55) return false;
    heap.delNode(3);
    if(heap.findMin() != -55) return false;
    heap.delNode(2);
    if(heap.findMin() != -55) return false;
    return true;
}

bool general_test(){
    int arr[1]={12};
    MinHeap heap(1,arr);
    heap.delNode(2);
    if(heap.findMin()!=12) return false;
    heap.delNode(0);
    if(heap.findMin()!=0) return false;
    heap.insert(13);
    if(heap.findMin()!=13) return false;
    heap.insert(-1);
    if(heap.findMin()!=-1) return false;
    heap.delMin();
    if(heap.findMin()!=13) return false;
    heap.insert(14);
    heap.insert(15);
    heap.insert(16);
    heap.insert(17);
    heap.insert(-100);
    if(heap.findMin() != -100) return false;
    heap.delMin();
    heap.delMin();
    heap.delMin();
    heap.delMin();
    heap.delMin();
    heap.delMin();
    if(heap.findMin()!=0) return false;
    heap.insert(-5);
    heap.insert(-6);
    heap.insert(-7);
    heap.insert(-8);
    int** indexes=heap.getIndexes();
    for(int i=0;i<4;i++){
        if(i != *indexes[i]) return false;
    }
    heap.delNode(3);
    heap.delNode(0);
    heap.delNode(0);
    heap.delNode(0);
    if(heap.findMin()!=0) return false;
    return true;
}

int main(int argc, const char**argv) {
    RUN_TEST(getIndexes);
    RUN_TEST(insert);
    RUN_TEST(getMin);
    RUN_TEST(decKey);
    RUN_TEST(delNode);
    RUN_TEST(general_test);
}