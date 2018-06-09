//
// Created by Ilya on 6/8/2018.
//

#include "exceptions.h"
#include <assert.h>
#include "MinHeap.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, const char**argv) {
    int arr[11]={1,-6,7,4,-5,2,4,52,99,-101,3};
    MinHeap h(11,arr);
    h.printArr();
    cout<<"Now inserting a new element: "<<endl;
    h.insert(-102);
    cout<<"*-102* should be the smallest"<<endl;
    cout<< h.findMin()<< endl;
    cout<<"remove *2*"<<endl;
    h.delNode(5);
    h.printArr();
}