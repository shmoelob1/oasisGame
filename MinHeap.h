
#ifndef WET2_MINHEAP_H
#define WET2_MINHEAP_H

#include "DynamicArray.h"

class MinHeap {
private:
    DynamicArray arr;
    void siftDown(int k){
        int childLeft = 2*k + 1;
        int childRight = 2*k + 2;
        int l = arr.getSize();
        if(childLeft >= l)
            return; //index is a leaf
        int minK;
        minK = k;
        if(arr[k]->getClanId() > arr[childLeft]->getClanId())
            minK = childLeft;
        if((childRight < l) && (arr[minK]->getClanId() > arr[childRight]->getClanId()))
            minK = childRight;
        if(minK != k)
        {
            Clan *clan1 = arr[k];
            arr.getIndexClan(k)->setIndex(minK);
            arr.getIndexClan(minK)->setIndex(k);
            arr.setClanPtr(k,arr[minK]);
            arr.setClanPtr(minK,clan1);
            siftDown(minK); }
    }

    void siftTheRoad(){
        int l = arr.getSize();
        l = (l/2) + 1;
        for(int i=l; i>=0; --i)
        {
            siftDown(i); }
    }


    void dec(int k,int m){
        arr[k]->setClanId(m);
        siftUp(k);
    }

    void siftUp(int k){
        if(k == 0)
            return;
        int parentOfk = (k-1)/2;

        if(arr[parentOfk]->getClanId() > arr[k]->getClanId() ) {
            Clan *clan1 = arr[parentOfk];
            arr.getIndexClan(parentOfk)->setIndex(k);
            arr.getIndexClan(k)->setIndex(parentOfk);
            arr.setClanPtr(parentOfk,arr[k]);
            arr.setClanPtr(k,clan1);
            siftUp(parentOfk);
        }
    }

public:
    MinHeap(int l,Clan **ptrs):arr(l){
        for(int i = 0; i < l; ++i) {
            ptrs[i]->setIndex(i);
            arr.setClanPtr(i, ptrs[i]);
            arr.sizeUp();
        }
        siftTheRoad();
    }

    void insert(Clan* newClan){
        int l = arr.getSize();
        newClan->setIndex(l);
        arr.insert(newClan);
        siftUp(l);
    }

    void removeMin(int k) {
        dec(k, -1);
        deleteMin();
    }

    int getMin(){
        return arr[0]->getClanId();
    }

    void deleteMin(){
        int l = arr.getSize();
        if(l == 0) return;
        Clan *clan1 = arr[0];
        arr.getIndexClan(0)->setIndex(-2);
        arr.getIndexClan(l-1)->setIndex(0);
        arr.setClanPtr(0,arr[l-1]);
        arr.setClanPtr(l-1,clan1);
        arr.remove(l-1);

        siftDown(0);
    }
};
#endif //WET2_MINHEAP_H
