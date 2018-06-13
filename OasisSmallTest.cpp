//
// Created by Ilya on 12-Jun-18.
//
#include "testMacros.h"
#include "Oasis.h"

bool testInit(){
    //int arr[3]={12,23,34};
    //Oasis os(3,arr);
    int arr2[10]={1,-2,4,-54,23,54,66,-66,8,-8};
    Oasis os2(10,arr2);
    //Oasis os3(1,arr);
    return true;
}

int main(){
    RUN_TEST(testInit);
}
