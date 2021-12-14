#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <cstdlib>
#include <iostream>
#include "Clan.h"

#define START_HASH_SIZE 10


template<class T>
class hashNode {
    T data_;
    int id_;
    hashNode<T> *next_;
public:
    void setData(T data) { this->data_ = data_; }

    hashNode<T>(T data, int id) : data_(data), id_(id), next_(NULL) {}

    hashNode<T> *getNext() {
        return next_;
    }
    T getData() {
        return data_;
    }

    int getId() {
        return id_;
    }

    void setNext(hashNode<T> *next) {
        this->next_ = next;
    }
};


template<class T>
class HashTable {
private:
    hashNode<T> **arr_;
    int size_, maximum_;

    int hashFunc(int id) {
        return id % maximum_;
    }

    void insertArr(T data, int id, hashNode<T> **arr) {
        int l = hashFunc(id);
        if (!arr[l]) {
            arr[l] = new hashNode<T>(data, id);
            return;
        }
        hashNode<T> *curr = arr[l];
        while (curr->getNext()) {
            curr = curr->getNext();
        }
        curr->setNext(new hashNode<T>(data, id));
    }

    void inserNew(hashNode<T> **target, bool del) {
        int big;
        if (del) big = maximum_ * 2;
        else big = maximum_ / 2;
        for (int i = 0; i < big; i++) {
            hashNode<T> *node = arr_[i];
            while (node) {
                insertArr(node->getData(), node->getId(), target);
                node = node->getNext();
            }
        }
    }

    void DestroyRecursive(hashNode<T> *node) {
        if (node) {
            delete node->getData();
            node->setData(NULL);
            DestroyRecursive(node->getNext());
        }
    }

    void eraseTable(hashNode<T> **arr) {
        for (int i = 0; i < maximum_; i++) {
            hashNode<T> *node = arr[i];
            while (node) {
                hashNode<T> *prev = node;
                node = node->getNext();
                delete prev;
            }
            arr[i] = NULL;
        }
    }
    void deleteData(hashNode<T> **arr) {
        for (int i = 0; i < maximum_; i++) {
            hashNode<T> *node = arr[i];
            while (node) {
                hashNode<T> *prev = node;
                node = node->getNext();
                delete prev->getData();
                delete prev;
            }
            arr[i] = NULL;
        }
    }

    void updateSize() {
        hashNode<T> **newArr = new hashNode<T> *[maximum_ * 2];
        for (int i = 0; i < 2 * maximum_; i++)
            newArr[i] = NULL;
        maximum_ *= 2;
        inserNew(newArr, false);
        maximum_ /= 2;
        eraseTable(arr_);
        delete[] arr_;
        arr_ = newArr;
        maximum_ *= 2;
    }

public:
    HashTable<T>() : size_(0), maximum_(START_HASH_SIZE) {
        arr_ = new hashNode<T> *[START_HASH_SIZE];
        for (int i = 0; i < START_HASH_SIZE; i++)
            arr_[i] = NULL;
    }

    ~HashTable<T>() {
        deleteData(arr_);
        delete[] arr_;
    }

    T getData(int id, int *flag) {
        int k = hashFunc(id);
        hashNode<T> *node = arr_[k];
        while (node != NULL) {
            if (node->getId() == id) return node->getData();
            node = node->getNext();
        }
        *flag = 1;
        return NULL;
    }


    void insert(T data, int id) {
        int flag = 0;
        getData(id, &flag);
        if (flag) {
            if (size_ + 1 > maximum_) {
                updateSize();
            }
            int k = hashFunc(id);
            if (!arr_[k]) {
                arr_[k] = new hashNode<T>(data, id);
            } else {
                hashNode<T> *node = arr_[k];
                while (node->getNext()) {
                    node = node->getNext();
                }
                node->setNext(new hashNode<T>(data, id));
            }
            size_++;
            return;
        }
    }
};

#endif //





