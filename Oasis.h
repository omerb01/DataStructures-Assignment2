//
// Created by Omer on 07/06/2018.
//

#ifndef DATASTRUCTURES_HW2_OASIS_H
#define DATASTRUCTURES_HW2_OASIS_H

#include "HashTable.h";
#include "MinHeap.h";
#include "AVLTree.h"

class Player {
    int playerID;
    int score;
};

class DoubleKey {
    int key1;
    int key2;

public:

    DoubleKey() {
        key1 = -1;
        key2 = -1;
    }

    DoubleKey(int key1, int key2) {
        this->key1 = key1;
        this->key2 = key2;
    }

    bool operator==(const DoubleKey &key);

    bool operator!=(const DoubleKey &key);

    bool operator<(const DoubleKey &key);

    bool operator<=(const DoubleKey &key);

    bool operator>(const DoubleKey &key);

    bool operator>=(const DoubleKey &key);
};

class Clan {
    int clanID;
    int heap_index;
    AVLTree<Player, DoubleKey> players;
};

class Oasis {
    HashTable<Clan> clans;
    MinHeap clan_ids;

public:

    Oasis(int n, int *clanIDs);

    Oasis(const Oasis& oasis) = delete;

    Oasis &operator=(const Oasis *oasis) = delete;

    void addClan(int clanID);

    void addPlayer(int playerID, int score, int clanID);

    void clanFight(int clanID1, int clanID2, int k1, int k2);

    void getMinClan(int* clanID);
};

#endif //DATASTRUCTURES_HW2_OASIS_H
