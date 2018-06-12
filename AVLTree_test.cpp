//
// Created by Omer on 06/05/2018.
//

#include "testMacros.h"
#include <iostream>
#include "AVLTree.h"
#include "Oasis.h"
#include "exceptions.h"

template<typename T>
bool areArraysEqual(T *a, T *b, int n) {
    if (a == nullptr && b == nullptr) return true;
    if (a == nullptr || b == nullptr) return false;
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

template<typename T, class Key>
bool areTreesEqual(const AVLTree<T, Key> &tree1, const AVLTree<T, Key> &tree2, int size) {
    T *inArray1 = tree1.inOrderToArray();
    T *preArray1 = tree1.preOrderToArray();
    T *inArray2 = tree2.inOrderToArray();
    T *preArray2 = tree2.preOrderToArray();

    bool result = areArraysEqual(inArray1, inArray2, size) &&
                  areArraysEqual(preArray1, preArray2, size);

    delete[] inArray1;
    delete[] inArray2;
    delete[] preArray1;
    delete[] preArray2;
    return result;
}

bool testInsertRR() {
    AVLTree<int, int> tree1;
    AVLTree<int, int> tree2;

    tree1.insert(6, 6);
    tree1.insert(8, 8);
    tree1.insert(1, 1);
    tree1.insert(7, 7);
    tree1.insert(9, 9);

    //Roll RR
    tree1.insert(10, 10);


    tree2.insert(8, 8);
    tree2.insert(1, 1);
    tree2.insert(7, 7);
    tree2.insert(10, 10);
    tree2.insert(9, 9);
    tree2.insert(6, 6);

    ASSERT_FALSE(areTreesEqual(tree1, tree2, 6));
    return true;
}

bool testInsertRL() {
    AVLTree<int, int> tree1;
    AVLTree<int, int> tree2;

    tree1.insert(6, 6);
    tree1.insert(1, 1);
    tree1.insert(10, 10);
    tree1.insert(9, 9);
    tree1.insert(12, 12);

    //Roll RL
    tree1.insert(8, 8);

    tree2.insert(12, 12);
    tree2.insert(10, 10);
    tree2.insert(6, 6);
    tree2.insert(1, 1);
    tree2.insert(8, 8);
    tree2.insert(9, 9);
    ASSERT_FALSE(areTreesEqual(tree1, tree2, 5));
    return true;
}

bool testInsertLL() {
    AVLTree<int, int> tree1;
    tree1.insert(2, 2);
    tree1.insert(1, 1);
    tree1.insert(7, 7);
    tree1.insert(5, 5);

    // LL roll
    tree1.insert(3, 3);

    AVLTree<int, int> tree2;
    tree2.insert(2, 2);
    tree2.insert(5, 5);
    tree2.insert(1, 1);
    tree2.insert(7, 7);
    tree2.insert(3, 3);

    ASSERT_TRUE(areTreesEqual(tree1, tree2, 5));

    return true;
}

bool testInsertLR() {
    AVLTree<int, int> tree1;
    AVLTree<int, int> tree2;

    tree1.insert(5, 5);
    tree1.insert(1, 1);
    tree1.insert(6, 6);
    tree1.insert(0, 0);
    tree1.insert(2, 2);

    //LR roll
    tree1.insert(3, 3);

    tree2.insert(2, 2);
    tree2.insert(0, 0);
    tree2.insert(1, 1);
    tree2.insert(5, 5);
    tree2.insert(3, 3);
    tree2.insert(6, 6);


    ASSERT_FALSE(areTreesEqual(tree1, tree2, 6));

    return true;
}

bool testRemoveRR() {
    AVLTree<int, int> tree1;
    AVLTree<int, int> tree2;

    tree1.insert(6, 6);
    tree1.insert(8, 8);
    tree1.insert(1, 1);
    tree1.insert(7, 7);
    tree1.insert(10, 10);
    tree1.insert(11, 11);
    tree1.insert(9, 9);
    tree1.insert(12, 12);
    //Roll RR
    tree1.remove(10);

    tree2.insert(8, 8);
    tree2.insert(6, 6);

    tree2.insert(11, 11);
    tree2.insert(1, 1);
    tree2.insert(7, 7);
    tree2.insert(9, 9);
    tree2.insert(12, 12);

    ASSERT_TRUE(areTreesEqual(tree1, tree2, 7));
    return true;
}

bool testRemoveRL() {
    AVLTree<int, int> tree1;
    AVLTree<int, int> tree2;

    tree1.insert(5, 5);
    tree1.insert(2, 2);
    tree1.insert(8, 8);
    tree1.insert(4, 4);
    tree1.insert(6, 6);
    tree1.insert(10, 10);
    tree1.insert(1, 1);
    tree1.insert(3, 3);
    tree1.insert(7, 7);
    tree1.insert(9, 9);
    tree1.insert(12, 12);
    tree1.insert(11, 11);
    //Roll RL
    tree1.remove(1);

    tree2.insert(8, 8);
    tree2.insert(5, 5);
    tree2.insert(10, 10);
    tree2.insert(3, 3);
    tree2.insert(6, 6);
    tree2.insert(9, 9);
    tree2.insert(12, 12);
    tree2.insert(2, 2);
    tree2.insert(4, 4);
    tree2.insert(7, 7);
    tree2.insert(11, 11);


    ASSERT_TRUE(areTreesEqual(tree1, tree2, 11));
    return true;
}

bool testRemoveLL() {
    AVLTree<int, int> tree1;
    AVLTree<int, int> tree2;

    tree1.insert(5, 5);
    tree1.insert(3, 3);
    tree1.insert(8, 8);
    tree1.insert(2, 2);
    tree1.insert(4, 4);
    tree1.insert(7, 7);
    tree1.insert(11, 11);
    tree1.insert(1, 1);
    tree1.insert(6, 6);
    tree1.insert(10, 10);
    tree1.insert(12, 12);
    tree1.insert(9, 9);

    // Roll LL:
    tree1.remove(4);

    tree2.insert(8, 8);
    tree2.insert(5, 5);
    tree2.insert(11, 11);
    tree2.insert(2, 2);
    tree2.insert(7, 7);
    tree2.insert(10, 10);
    tree2.insert(12, 12);
    tree2.insert(1, 1);
    tree2.insert(3, 3);
    tree2.insert(6, 6);
    tree2.insert(9, 9);

    ASSERT_TRUE(areTreesEqual(tree1, tree2, 11));
    return true;
}

bool testRemoveLR() {
    AVLTree<int, int> tree1;
    AVLTree<int, int> tree2;

    tree1.insert(10, 10);
    tree1.insert(1, 1);
    tree1.insert(12, 12);
    tree1.insert(0, 0);
    tree1.insert(2, 2);
    tree1.insert(13, 13);
    tree1.insert(5, 5);
    tree1.insert(4, 4);

    //LR Roll:
    tree1.remove(13);

    tree2.insert(4, 4);
    tree2.insert(1, 1);
    tree2.insert(10, 10);
    tree2.insert(0, 0);
    tree2.insert(2, 2);
    tree2.insert(5, 5);
    tree2.insert(12, 12);
    return true;
}

bool testFind() {
    AVLTree<int, int> tree1;
    tree1.insert(10, 10);
    tree1.insert(1, 1);
    tree1.insert(12, 12);
    tree1.insert(0, 0);
    tree1.insert(2, 2);
    tree1.insert(13, 13);
    tree1.insert(5, 5);
    tree1.insert(4, 4);

    ASSERT_EXCEPTION(tree1.find(14), AVLElementNotFound);
    ASSERT_EXCEPTION(tree1.find(300), AVLElementNotFound);
    ASSERT_EXCEPTION(tree1.find(14), AVLElementNotFound);
    ASSERT_TRUE(tree1.find(10) == 10);
    ASSERT_TRUE(tree1.find(13) == 13);
    ASSERT_TRUE(tree1.find(1) == 1);
    return true;
}

bool testGetWeakTree() {
    AVLTree<int, DoubleKey> tree1;
    tree1.insert(3, DoubleKey(3,3));
    tree1.insert(6, DoubleKey(6,6));
    tree1.insert(1, DoubleKey(1,1));
    tree1.insert(2, DoubleKey(2,2));
    tree1.insert(0, DoubleKey(0,0));

    AVLTree<int, DoubleKey> tree2;
    tree2.insert(3, DoubleKey(3,3));
    tree2.insert(6, DoubleKey(6,6));
    tree2.insert(1, DoubleKey(1,1));
    tree2.insert(0, DoubleKey(0,0));

    char c = tree1.getWeakTree(tree1,tree2,5,5);

    AVLTree<int, DoubleKey> tree3;
    AVLTree<int, DoubleKey> tree4;
    c = tree3.getWeakTree(tree3,tree4,5,5);

    return true;
}

int main() {
    RUN_TEST(testInsertLL);
    RUN_TEST(testInsertLR);
    RUN_TEST(testInsertRR);
    RUN_TEST(testInsertRL);
    RUN_TEST(testRemoveRR);
    RUN_TEST(testRemoveRL);
    RUN_TEST(testRemoveLL);
    RUN_TEST(testRemoveLR);
    RUN_TEST(testFind);
    RUN_TEST(testGetWeakTree);
    return 0;
}