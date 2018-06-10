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
    MinHeap h(0,nullptr);
    int *index=new int();
    int *index2=new int();
    h.insert(-9,index);
    h.insert(-10,index2);
    h.printArr();
    cout << *index << endl;
}