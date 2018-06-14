//
// Created by Ilya on 12-Jun-18.
//
#include "../testMacros.h"
#include "../Oasis.h"
#include "../exceptions.h"

bool testInit(){
    int arr[3]={12,23,34};
    Oasis os(3,arr);
    int arr2[10]={1,-2,4,-54,23,54,66,-66,8,-8};
    ASSERT_EXCEPTION(Oasis os2(10,arr2), OasisInvalidInput);
    Oasis os3(1,arr);
    return true;
}

bool testAddClan(){
    int arr[3]={12,23,34};
    Oasis os(3,arr);
    ASSERT_EXCEPTION(os.addClan(-12), OasisInvalidInput);
    os.addClan(1);
    Oasis os2(0,nullptr);
    os2.addClan(1);

    return true;
}

int main(){
    RUN_TEST(testInit);
    RUN_TEST(testAddClan);
}
