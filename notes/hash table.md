# Hash Table (雜湊表) - 深度解析

雜湊表（Hash Table）是一種透過 **鍵 (Key)** 來直接存取 **值 (Value)** 的資料結構。它透過一個關鍵的「雜湊函數」，將抽象的鍵轉換成陣列的索引，從而實現接近常數時間的存取速度。

---

## 1. 核心原理：雜湊函數 (Hash Function)

雜湊函數的作用是將任意長度的輸入（Key），經由計算法則轉換成固定範圍的整數輸出（Index）。

$$Index = f(Key) \pmod{ArraySize}$$



### 一個優秀的雜湊函數應具備：
* **計算快速**：不應成為效能瓶頸。
* **均勻分佈**：盡可能將不同的 Key 散佈到不同的索引處，減少碰撞。
* **確定性**：相同的輸入必須得到相同的輸出。

---

## 2. 雜湊碰撞 (Collision Handling)

當兩個不同的 Key 經過雜湊運算後得到相同的索引時，就稱為**碰撞**。這是雜湊表最核心的挑戰。



### 2.1 鏈結法 (Separate Chaining)
在每個陣列位置（Bucket）儲存一個 **Linked List**。當碰撞發生時，將新資料接在鏈結串列的末端。
* **優點**：實作簡單，資料量超過陣列長度時仍可運作。
* **缺點**：如果碰撞太多，搜尋效率會退化成 $O(n)$。

### 2.2 開放定址法 (Open Addressing)
當碰撞發生時，按照某種規則尋找陣列中下一個空的格子。
1.  **線性探測 (Linear Probing)**：依序往後找 (Index + 1, +2...)。易產生「集群 (Clustering)」問題。
2.  **平方探測 (Quadratic Probing)**：以平方距離尋找 (Index + $1^2$, + $2^2$...)。
3.  **雙重雜湊 (Double Hashing)**：使用第二個雜湊函數來計算跳躍距離。



---

## 3. 效能與裝載因子 (Load Factor)

### 3.1 時間複雜度
| 操作 | 平均情況 | 最壞情況 (全碰撞) |
| :--- | :---: | :---: |
| **搜尋 (Search)** | $O(1)$ | $O(n)$ |
| **插入 (Insertion)** | $O(1)$ | $O(n)$ |
| **刪除 (Deletion)** | $O(1)$ | $O(n)$ |

### 3.2 裝載因子 ($\alpha$)
$$\alpha = \frac{\text{已儲存的元素數量}}{\text{雜湊表總長度}}$$
* 當 $\alpha$ 過高時（通常建議 > 0.7），碰撞機率會劇增。
* **Rehashing (重新雜湊)**：當裝載因子超過閾值，系統會建立一個更大的陣列（通常是 2 倍大），並將所有資料重新計算雜湊值存入。

---

## 4. 程式碼實作範例 (C++)
使用鏈結法 (Separate Chaining) 的簡單範例：

```cpp
#include <iostream>
#include <list>
#include <vector>

class HashTable {
    int BUCKET; 
    std::vector<std::list<int>> table;

public:
    HashTable(int b) : BUCKET(b) {
        table.resize(BUCKET);
    }

    int hashFunction(int key) {
        return key % BUCKET;
    }

    void insertItem(int key) {
        int index = hashFunction(key);
        table[index].push_back(key);
    }

    void deleteItem(int key) {
        int index = hashFunction(key);
        table[index].remove(key);
    }

    bool searchItem(int key) {
        int index = hashFunction(key);
        for (int x : table[index]) {
            if (x == key) return true;
        }
```
## 5. 優缺點

### 優點
- 搜尋極快：在平均情況下提供 $O(1)$ 的速度。
- 適合 Key-Value 結構：如字典、帳號查詢系統。

## 缺點
- 無序性：資料在記憶體中是散亂的，不適合需要「排序」或「範圍搜尋」的場景。
- 空間利用率：為了減少碰撞，通常需要預留較大的空間。
        return false;
    }
};
