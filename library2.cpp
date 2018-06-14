//
// Created by Omer on 13/06/2018.
//

#include "Oasis.h"
#include "library2.h"

#define GENERIC_OUTPUT($$command$$) \
if(DS == nullptr) return INVALID_INPUT; \
try { \
$$command$$; \
return SUCCESS; \
} \
catch (OasisInvalidInput &e) { \
return INVALID_INPUT; \
} \
catch (std::bad_alloc &e) { \
return ALLOCATION_ERROR; \
} \
catch (OasisFailure &e) { \
return FAILURE; \
}

void* init(int n, int *clanIDs) {
    Oasis *DS;
    try {
        DS = new Oasis(n, clanIDs);
    }
    catch (OasisInvalidInput& e) {
        return nullptr;
    }
    return (void*)DS;
}

StatusType addClan(void *DS, int clanID) {
    GENERIC_OUTPUT(((Oasis*)DS)->addClan(clanID));
}

StatusType addPlayer(void *DS, int playerID, int score, int clan) {
    GENERIC_OUTPUT(((Oasis*)DS)->addPlayer(playerID, score, clan));
}

StatusType clanFight(void *DS, int clan1, int clan2, int k1, int k2) {
    GENERIC_OUTPUT(((Oasis*)DS)->clanFight(clan1, clan2, k1, k2));
}

StatusType getMinClan(void *DS, int *clan) {
    GENERIC_OUTPUT(((Oasis*)DS)->getMinClan(clan));
}

void quit(void** DS) {
    if(DS == nullptr) return;
    if(*DS == nullptr) return;
    delete (Oasis*)(*DS);
    *DS = nullptr;
}