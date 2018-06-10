//
// Created by Omer on 10/06/2018.
//

#include "Oasis.h"
#include "exceptions.h"

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

void Oasis::clanFight(int clanID1, int clanID2, int k1, int k2) {
    if(k1 == 0 || k2 == 0 || clanID1 < 0 || clanID2 < 0) throw OasisInvalidInput();
    if(clanID1 == clanID2) throw OasisFailure();
    try {
        Clan& clan1 = clans.search(clanID1);
        Clan& clan2 = clans.search(clanID2);
        if(clan1.heap_index == nullptr || clan2.heap_index == nullptr) throw OasisFailure();
        if(clan1.num_of_players < k1 || clan2.num_of_players < k2) throw OasisFailure();


    }
    catch (HashElementNotFound &e) {
        throw OasisFailure();
    }
}