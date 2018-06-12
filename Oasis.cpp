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

class ScoresSummary {
    int sum;
public:
    ScoresSummary() {
        sum = 0;
    }

    int get() {
        return sum;
    }

    void operator()(Player player) {
        sum += player.score;
    }
};

Oasis::Oasis(int n, int *clanIDs) {
    try {
        if (!(n < 2 || clanIDs == nullptr)) {
            MinHeap clans_heap(n, clanIDs);
            clans_indexes = clans_heap.getIndexes(); //O(n)
            size=n;
            last=n-1;
            int *clanSortedIDs = clans_heap.getSortedID(); //O(n)
            Clan **clans=new Clan*[n];
            for (int i = 0; i < n; i++) {
                Clan *new_clan = new Clan();
                new_clan->clanID = clanSortedIDs[i];
                new_clan->heap_index = clans_indexes[i];
                clans[i]=new_clan;
            }

            HashTable<Clan> clans_hash_table(n, clans, clanIDs);
            for(int i=0;i<n;i++){
                delete clans[i];
            }
            delete []clanSortedIDs;
            delete []clans;

            this->clans = clans_hash_table;
            this->clan_ids=clans_heap;
        }
    } catch (std::bad_alloc &ba) {
        throw OasisAlloctionFailure();
    }
}

void Oasis::addClan(int clanID) {
    if (clanID < 0 /*TODO:check if oasis is empty*/) {
        throw OasisInvalidInput();
    }
    try {
        try{
            this->clans.search(clanID); //O(1)
            throw OasisFailure();
        }catch(HashElementNotFound &he){
            Clan *new_clan = new Clan();
            new_clan->clanID = clanID;
            int* new_clan_ptr=this->clan_ids.insert(
                    clanID);//O(log(n))
            new_clan->heap_index=new_clan_ptr;
                    clans.insert(new_clan,clanID);
            last++;
            if(last>=size){
                size*=2;
                int** new_array = new int*[size];
                for(int i=0;i<=last-1;i++){
                    new_array[i]=this->clans_indexes[i];
                }
                new_array[last]=new_clan_ptr;
                delete []clans_indexes;
                clans_indexes=new_array;
            }else{
                clans_indexes[last]=new_clan_ptr;
            }
            delete new_clan;
        }

    } catch (std::bad_alloc &ba) {
        throw OasisAlloctionFailure();
    }
}

void Oasis::addPlayer(int playerID, int score, int clanID) {
    if (playerID < 0 || score < 0 || clanID < 0 /*TODO:Oasis=NULL*/) {
        throw OasisInvalidInput();
    }
    try {
        Clan players_clan = this->clans.search(clanID); //O(1)
        Player new_player(playerID, score);
        DoubleKey new_key(playerID, score);
        players_clan.players.insert(new_player, new_key); //O(log(m))
    } catch (OasisException &os) {
        throw OasisFailure();
    }
}

void Oasis::clanFight(int clanID1, int clanID2, int k1, int k2) {
    if (k1 == 0 || k2 == 0 || clanID1 < 0 || clanID2 < 0)
        throw OasisInvalidInput();
    if (clanID1 == clanID2) throw OasisFailure();
    try {
        Clan &clan1 = clans.search(clanID1);
        Clan &clan2 = clans.search(clanID2);

        if (clan1.heap_index == nullptr || clan2.heap_index == nullptr)
            throw OasisFailure();
        if (clan1.num_of_players < k1 || clan2.num_of_players < k2)
            throw OasisFailure();

        ScoresSummary top_scores1;
        ScoresSummary top_scores2;
        clan1.players.analizeTopElements(k1, top_scores1);
        clan2.players.analizeTopElements(k2, top_scores2);

        Clan *conquered_clan;
        if (top_scores1.get() == top_scores2.get()) {
            if (clan1.clanID < clan2.clanID) conquered_clan = &clan2;
            else conquered_clan = &clan1;
        } else if (top_scores1.get() > top_scores2.get())
            conquered_clan = &clan2;
        else conquered_clan = &clan1;
        //TODO: delete with delNode
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

Oasis::~Oasis(){
    for(int i=0;i<=last;i++){
        delete clans_indexes[i];
    }
    delete []clans_indexes;
}