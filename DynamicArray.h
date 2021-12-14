#ifndef WET2_DYNAMICARRAY_H
#define WET2_DYNAMICARRAY_H

#include "Clan.h"


class DynamicArray {
private:
    Clan **arr_;
    int max_;
    int size_;

public:
    /**
     * constructor with default value 2
     * @param init
     */
    explicit DynamicArray(int init=2){
        size_ = 0;
        max_ = init;
        arr_ = new Clan*[max_];
        int i;
        for (i = 0; i < max_; i++) {
            arr_[i] = NULL;
        }
    };
    /**
     * Destructor with no parameters
     */
    ~DynamicArray(){
        delete[] arr_;
    };

    /**
     * Insert a new clan to the array
     * Allocate more or less memory
     * @param x
     */
    void insert(Clan *x){
        ifResizeInsert();
        arr_[size_] = x;
        size_++;
    };

    /**
     * Delete an existing clan from array
     * @param k
     */
    void remove(int l){
        size_--;
        arr_[l] = NULL;
        ifResizeRemove();
    };

    void setClanPtr(int index,Clan *ptr){
        arr_[index] = ptr;
    };


    int getSize(){
        return size_;
    };


    void sizeUp(){
        size_++;
    }


    Clan* getIndexClan(int index){
        return arr_[index];
    };

    /**
     * resize the array with boolean parameter
     * 1=resize pow of 2
     * 0=resize pow of 0.5
     * @param flag
     */
    void resizeArr(bool flag){
        int size1 = 0;
        Clan **clan1;
        if(flag){
            size1 = max_ * 2;
            clan1 = new Clan*[size1];
            for (int i = 0; i < (max_); i++) {
                clan1[i] = arr_[i];
            }
            for (int j = max_; j < size1; ++j) {
                clan1[j] = NULL;
            }
        }
        else{
            size1 = (0.5)*max_;  //Casting From Double To Int - Lower Bound
            clan1 = new Clan*[size1];
            for (int i = 0; i < size1; i++) {
                clan1[i] = arr_[i];
            }
        }
        max_ = size1;
        delete[] arr_;
        arr_ = clan1;
    };


    void ifResizeInsert(){
        if ( size_ == max_) {
            resizeArr(1);
        }
    };
    void ifResizeRemove(){
        if( size_ == (max_/4) + 1){
            resizeArr(0);
        }
    };
    Clan* operator[](int index){
        return arr_[index];
    }

};



#endif //WET2_DYNAMICARRAY_H
