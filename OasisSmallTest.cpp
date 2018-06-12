//
// Created by Ilya on 12-Jun-18.
//
#include "testMacros.h"
#include "Oasis.h"

bool testInit(){
    int arr[3]={12,23,34};
    Oasis os(3,arr);
    os.addClan(10);
    int minclan;
    os.getMinClan(&minclan);
    os.addPlayer(123,100,23);
    os.addClan(1);
    os.getMinClan(&minclan);
    cout << minclan << endl;
    return true;
}

int main(){
    RUN_TEST(testInit);
}
