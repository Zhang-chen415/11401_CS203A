/*
   ========================================
   hash_fn.cpp — implement your hash functions
   ========================================

   Description:
    This file contains the hash functions for integer and string keys.

   Development History:
    - 2025/11/11: Initial implementation
    - 2025/11/17: Refactored to use hash_fn.hpp

   Developer: Yu-Feng Huang <yfhuang@saturn.yzu.edu.tw>
 */
#include "hash_fn.hpp"

int myHashInt(int key, int m) {
    // TODO: replace with your own design
    long long int square = key * key;  //平方
    square /= 10; //不取個位數
    return square % m;
}

int myHashString(const std::string& str, int m) {
    unsigned long hash = 0;
    // TODO: replace with your own design
    for (int i = 0; i < str.size(); i++) {
        hash += (int)str[i];
    }
    long long int square = hash * hash; //平方
    square /= 10; //不取個位數

    return static_cast<int>(square % m);  // basic division method
}
