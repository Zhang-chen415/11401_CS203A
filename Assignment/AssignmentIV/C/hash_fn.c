/*
   ========================================
   hash_fn.c — implement your hash functions
   ========================================

   Description:
    This file contains the hash functions for integer and string keys.

   Development History:
    - 2025/11/11: Initial implementation
    - 2025/11/17: Refactored to use hash_fn.h

   Developer: 1131435張新誠 <s1131435@mail.yzu.edu.tw>
 */

#include "hash_fn.h"

int myHashInt(int key, int m) {
    // TODO: replace with your own design
   if (m <= 0) {
        printf("Error, m要為正整數, 接收到的m: %d\n", m);
        return 0;
    }

    // 使用 long long 防止 key * key 溢位
    long long int square = (long long int)key * key; 
    square /= 10;
    
    return (int)(square % m);
}

int myHashString(const char* str, int m) {
    if (m <= 0) {
        printf("Error, m要為正整數, 接收到的m: %d\n", m);
        return 0;
    }

    // 檢查字串指標是否為空或是空字串
    if (str == NULL || str[0] == '\0') {
        printf("Error, 字串是空的\n");
        return 0;
    }

    unsigned long hash = 0;
    // 在 C 語言中，使用 strlen() 或遍歷直到 '\0'
    for (int i = 0; str[i] != '\0'; i++) {
        hash += (unsigned char)str[i];
    }

    long long int square = (long long int)hash * hash; // 平方
    square /= 10; // 不取個位數

    return (int)(square % m);
}
