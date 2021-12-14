//
// Created by User on 6/12/2018.
//

#ifndef WET2_OASIS_H
#define WET2_OASIS_H


#include "HashTable.h"
#include "MinHeap.h"
#include "library2.h"
#include <stdlib.h>

class Oasis {
private:
    int numberOfClans, numberOfPlayers;
    HashTable<Clan *> *clans;
    AVLTree<int, int> *players;
    MinHeap *minClans;

    void outHeap(Clan *clan) {
        minClans->removeMin(clan->getIndex());
        clan->setConquer(true);
    }

public:
    Oasis() : numberOfClans(0), numberOfPlayers(0) {
        clans = new HashTable<Clan *>();
        players = new AVLTree<int, int>();
        minClans = new MinHeap(0, NULL);
    };

    Oasis(int n, int *clansId) : numberOfClans(n), numberOfPlayers(0) {
        this->clans = new HashTable<Clan *>();
        this->players = new AVLTree<int, int>();
        Clan **clansArray = new Clan *[n];
        for (int i = 0; i < n; i++) {
            Clan *c = new Clan(clansId[i]);
            this->clans->insert(c, clansId[i]);
            clansArray[i] = c;
        }
        minClans = new MinHeap(n, clansArray);
        delete[] clansArray;
    }

    StatusType getMinClan(int *clan);

    StatusType addClan(int clanID);

    StatusType addPlayer(int playerID, int score, int clan);

    StatusType clanFight(int clan1, int clan2, int k1, int k2);

    ~Oasis() {
        delete clans;
        delete players;
        delete minClans;
    }
};

StatusType Oasis::addClan(int clanId) {
    int flag = 0;
    clans->getData(clanId, &flag);
    if (!flag) {
        return FAILURE;
    }
    Clan *clan1 = new Clan(clanId);
    clans->insert(clan1, clanId);
    minClans->insert(clan1);
    numberOfClans++;  //Count the clans
    return SUCCESS;
}

StatusType Oasis::addPlayer(int playerID, int score, int clan) {
    if (players->findBYKey(playerID)) {
        return FAILURE;
    }
    int i = 0;
    Clan *c = clans->getData(clan, &i);
    if (c == NULL)
        return FAILURE;
    c->addPlayerToClan(playerID, score);
    this->players->insert(playerID, playerID);
    return SUCCESS;
}

StatusType Oasis::clanFight(int clan1, int clan2, int k1, int k2) {
    int i = 0;
    if (clan1 == clan2)
        return FAILURE;
    Clan *c1 = clans->getData(clan1, &i);
    Clan *c2 = clans->getData(clan2, &i);
    if (c1 == NULL || c2 == NULL)
        return FAILURE;
    if (c1->getConquer() || c2->getConquer())
        return FAILURE;
    if (c1->getNumberOfPlayers() < k1 || c2->getNumberOfPlayers() < k2)
        return FAILURE;
    int sum1 = c1->getScore(k1);
    int sum2 = c2->getScore(k2);
    Clan *loser;
    if (sum1 > sum2) {
        loser = c2;
    } else if (sum1 < sum2) {
        loser = c1;
    } else {
        if (clan1 < clan2) {
            loser = c2;
        } else {
            loser = c1;
        }
    }
    this->outHeap(loser);
    return SUCCESS;
}

StatusType Oasis::getMinClan(int *clan) {
    *clan = this->minClans->getMin();
    return SUCCESS;
}

#endif //WET2_OASIS_H
