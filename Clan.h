/**
 * Clan Class
 */

#ifndef WET1_CLAN_H
#define WET1_CLAN_H
#include "avlRanked.h"
#include "avl.h"

class Clan {
    int id;
    int index;
    int numberOfPlayers;
    bool conquer;
    //Clan* minHeap;
    AVLRankedTree *playerScores;
public:
    Clan(int id_) : id(id_),index(-2),numberOfPlayers(0)
            ,conquer(false)/*,minHeap(NULL)*/ {
        this->playerScores = new AVLRankedTree();
    };

    bool getConquer(){
        return this->conquer;
    }

    void setConquer(bool pred){
        this->conquer=pred;
    }

    int getClanId(){
        return this->id;
    }

    void setClanId(int id){
        this->id=id;
    }

    /*RankTree<player_key,comparePlayers> getPlayersTree(){
        return this->playerRankTree;
    }*/

    int getIndex(){
        return this->index;
    }

    void setIndex(int k){
        this->index=k;
    }

    /*void setMinHeap(Clan* clan){
        this->minHeap = clan;
    }*/


    ~Clan() {
        delete this->playerScores;
    }
    void addPlayerToClan(int id, int score){
        this->playerScores->insert(score);
        this->numberOfPlayers++;
    }
    int getScore(int k){
        return this->playerScores->getScore(k);
    }
    int getNumberOfPlayers(){
    return this->numberOfPlayers;
    }
};

#endif //WET1_CLAN_H