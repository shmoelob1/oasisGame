#include "library2.h"
#include "Oasis.h"

void* init(int n, int* clansIDs) {
    if(n < 2 || !clansIDs)
        return NULL;
    for(int i=0;i < n;i++){
        if(clansIDs[i] < 0)
            return NULL;
    }
    Oasis* DS = new Oasis(n, clansIDs);
    return (void*)DS;
}

StatusType getMinClan(void* DS, int* clan) {
    if(clan==NULL || DS==NULL)
        return INVALID_INPUT;
    return ((Oasis *) DS)->getMinClan(clan);
}

StatusType addClan(void *DS, int clanID){
    if(DS==NULL || clanID < 0)
        return INVALID_INPUT;
    return ((Oasis *) DS)->addClan(clanID);
}

StatusType addPlayer(void *DS, int playerID, int score, int clan){
    if(score<0 || playerID<0 || clan<0 || DS==NULL)
        return INVALID_INPUT;
    return ((Oasis *) DS)->addPlayer(playerID, score, clan);
}

StatusType clanFight(void *DS, int clan1, int clan2, int k1, int k2){
    if(k1<=0 || k2<=0 || DS==NULL || clan1<0 || clan2<0){
        return INVALID_INPUT;
    }
    return ((Oasis *) DS)->clanFight(clan1, clan2, k1, k2);
}

void quit(void **DS) {
    if (DS !=NULL && (*DS) != NULL) {
        delete ((Oasis *) (*DS));
        (*DS) = NULL;
    }
}