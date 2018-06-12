//
// Created by Omer on 07/06/2018.
//

#ifndef DATASTRUCTURES_HW2_OASIS_H
#define DATASTRUCTURES_HW2_OASIS_H

#include "HashTable.h"
#include "MinHeap.h"
#include "AVLTree.h"

class DoubleKey {
    int key1;
    int key2;

public:

    DoubleKey() {
        key1 = 0;
        key2 = 0;
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

    DoubleKey& operator+=(const DoubleKey& key);

    DoubleKey& operator-=(const DoubleKey& key);
};

class Player {
public:

    Player(int playerID, int score){
        this->playerID=playerID;
        this->score=score;
    }

    int playerID;
    int score;
};

class Clan {
public:
    int clanID;
    int* heap_index;
    int num_of_players;
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

    ~Oasis();
};

#endif //DATASTRUCTURES_HW2_OASIS_H
