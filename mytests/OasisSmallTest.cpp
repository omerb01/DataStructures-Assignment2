//
// Created by Ilya on 12-Jun-18.
//
#include "../testMacros.h"
#include "../Oasis.h"
#include "../exceptions.h"

bool testAddPlayer() {
    int arr[3] = {3, 4, 5};
    Oasis os(3, arr);
    os.addPlayer(10, 10, 3);
    return true;
}

int main() {
    RUN_TEST(testAddPlayer);
}
