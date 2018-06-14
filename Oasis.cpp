//
// Created by Omer on 10/06/2018.
//

#include "Oasis.h"
#include "exceptions.h"
//#include <new>

bool DoubleKey::operator==(const DoubleKey &key) {
    return key1 == key.key1 && key2 == key.key2;
}

bool DoubleKey::operator!=(const DoubleKey &key) {
    return !(*this == key);
}

bool DoubleKey::operator<(const DoubleKey &key) {
    if (key1 < key.key1) return true;
    if (key1 > key.key1) return false;
    return key2 > key.key2;
}

bool DoubleKey::operator<=(const DoubleKey &key) {
    return *this < key || *this == key;
}

bool DoubleKey::operator>(const DoubleKey &key) {
    return !(*this < key) && *this != key;
}

bool DoubleKey::operator>=(const DoubleKey &key) {
    return !(*this < key);
}

DoubleKey &DoubleKey::operator+=(const DoubleKey &key) {
    this->key1 += key.key1;
    this->key2 = this->key1;
    return *this;
}

DoubleKey &DoubleKey::operator-=(const DoubleKey &key) {
    this->key1 -= key.key1;
    this->key2 = this->key1;
    return *this;
}

Oasis::Oasis(int n, int *clanIDs) {
    try {
        if (n < 2 || clanIDs == nullptr) throw OasisInvalidInput();
        for (int i = 0; i < n; i++) {
            if (clanIDs[i] < 0) {
                throw OasisInvalidInput();
            }
        }
        MinHeap clans_heap(n, clanIDs);
        int **clans_indexes = clans_heap.getIndexes(); //O(n)
        int *clanSortedIDs = clans_heap.getSortedID(); //O(n)
        Clan **clans = new Clan *[n];
        for (int i = 0; i < n; i++) {
            Clan *new_clan = new Clan(clanSortedIDs[i]);
            new_clan->heap_index = clans_indexes[i];
            clans[i] = new_clan;
        }

        HashTable<Clan> clans_hash_table(n, clans, clanSortedIDs);
        for (int i = 0; i < n; i++) {
            delete clans[i];
        }
        delete[]clans_indexes;
        delete[]clanSortedIDs;
        delete[]clans;

        this->clans = clans_hash_table;
        this->clan_ids = clans_heap;
    } catch (std::bad_alloc &ba) {
        throw OasisAlloctionFailure();
    }
}

void Oasis::addClan(int clanID) {
    if (clanID < 0) {
        throw OasisInvalidInput();
    }
    try {
        Clan temp(clanID);
        if(clans.insert(&temp, clanID)) { // O(1)
            Clan& new_clan = clans.search(clanID); // O(1)
            int *new_clan_ptr = this->clan_ids.insert(clanID);// O(log(n))
            new_clan.heap_index = new_clan_ptr;
        }
        else {
            throw OasisFailure();
        }
    } catch (std::bad_alloc &ba) {
        throw OasisAlloctionFailure();
    }
}

void Oasis::addPlayer(int playerID, int score, int clanID) {
    if (playerID < 0 || score < 0 || clanID < 0) {
        throw OasisInvalidInput();
    }
    try {
        Clan &players_clan = this->clans.search(clanID); //O(1)
        Player new_player(playerID, score);
        DoubleKey new_key(score, playerID);
        if(!players.insert(playerID, playerID)) throw OasisFailure();
        players_clan.players.insert(new_player, new_key); //O(log(m))
        players_clan.num_of_players++;
    } catch (HashElementNotFound &e) {
        throw OasisFailure();
    }
}

void Oasis::clanFight(int clanID1, int clanID2, int k1, int k2) {
    if (k1 <= 0 || k2 <= 0 || clanID1 < 0 || clanID2 < 0)
        throw OasisInvalidInput();
    if (clanID1 == clanID2) throw OasisFailure();
    try {
        Clan &clan1 = clans.search(clanID1);
        Clan &clan2 = clans.search(clanID2);

        if (clan1.heap_index == nullptr || clan2.heap_index == nullptr)
            throw OasisFailure();
        if (clan1.num_of_players < k1 || clan2.num_of_players < k2)
            throw OasisFailure();

        char result = clan1.players.getWeakTree(clan1.players, clan2.players, k1, k2);

        Clan *conquered_clan;
        if (result == '=') {
            if (clan1.clanID < clan2.clanID) conquered_clan = &clan2;
            else conquered_clan = &clan1;
        } else if (result == '2') {
            conquered_clan = &clan2;
        } else { // result == '1'
            conquered_clan = &clan1;
        }

        clan_ids.decKey(*conquered_clan->heap_index, -1);
        conquered_clan->heap_index = nullptr;
        clan_ids.delMin();
    }
    catch (HashElementNotFound &e) {
        throw OasisFailure();
    }
}

void Oasis::getMinClan(int *clanID) {
    try {
        if (clanID == nullptr) {
            throw OasisInvalidInput();
        }
        *clanID = this->clan_ids.findMin();
    } catch (MinHeapElementNotFound &me) {
        throw OasisFailure();
    }
}

Oasis::~Oasis() {
    clan_ids.deleteHeap(&clan_ids);
}