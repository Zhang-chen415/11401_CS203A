/*
   ========================================
   hash_fn.cpp — implement your hash functions
   ========================================

   Description:
    This file contains the hash functions for integer and string keys.

   Development History:
    - 2025/11/11: Initial implementation
    - 2025/11/17: Refactored to use hash_fn.hpp

   Developer: 1131435張新誠 <s1131435@mail.yzu.edu.tw>
 */
#include <iostream>
#include "hash_fn.hpp"

using namespace std;

int myHashInt(int key, int m) {
    // TODO: replace with your own design
    if (m <= 0) {   //檢查table size是否有效
        cout << "Error, m要為正整數, 接收到的m: " << m << endl;
        return 0;
    }
    long long int square = key * key;  //平方
    square /= 10;
    return square % m;
}

int myHashString(const std::string& str, int m) {
    unsigned long hash = 0;
    // TODO: replace with your own design
    if (m <= 0) {   //檢查table size是否有效
        cout << "Error, m要為正整數, 接收到的m: " << m << endl;
        return 0;
    }
    if (str.empty()) { // 檢查字串是否為空的
        cout << "Error, 字串是空的" << endl;
        return 0;
    }
    for (int i = 0; i < str.size(); i++) {
        hash += str[i];
    }
    long long int square = hash * hash; //平方
    square /= 10; //不取個位數

    return static_cast<int>(square % m);  // basic division method
}
