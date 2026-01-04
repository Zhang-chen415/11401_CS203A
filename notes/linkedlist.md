# Linked List (鏈結串列)

鏈結串列（Linked List）是一種基礎的線性資料結構，但與陣列（Array）不同，它在記憶體中**不要求連續的空間**。它透過「指標（Pointer）」將各個分散的節點（Node）串聯起來。

---

## 1. 基本組成：節點 (Node)

每一個節點通常由兩個部分組成：
1.  **Data (資料)**：儲存實際的數值。
2.  **Next Pointer (指標/參照)**：儲存下一個節點的記憶體位址。



* **Head (頭節點)**：鏈結串列的第一個節點，是存取整個串列的入口。
* **Tail (尾節點)**：最後一個節點，其 Next 指標指向 `NULL` (或 `None`)。

---

## 2. 鏈結串列的分類

### 2.1 單向鏈結串列 (Singly Linked List)
最基本的型態，每個節點只知道下一個節點在哪裡，無法反向遍歷。

### 2.2 雙向鏈結串列 (Doubly Linked List)
每個節點有兩個指標：`Next` 指向後方，`Prev` 指向前方。
* **優點**：可以雙向遍歷，刪除節點時效率較高。
* **缺點**：每個節點需要額外空間儲存指標。

### 2.3 環狀鏈結串列 (Circular Linked List)
尾節點的 `Next` 指標指向頭節點，形成一個圓環。常用於需要輪轉資源的系統（如 CPU 排程）。

---

## 3. 時間複雜度分析 (Time Complexity)

鏈結串列的優勢在於**動態調整**，而非隨機存取。

| 操作 | 時間複雜度 | 說明 |
| :--- | :---: | :--- |
| **隨機存取 (Access)** | $O(n)$ | 必須從 Head 開始沿著指標一個一個找。 |
| **搜尋 (Search)** | $O(n)$ | 最壞情況需遍歷整個串列。 |
| **插入 (Insertion)** | $O(1)$ | 只要更改指標指向即可（前提是已找到位置）。 |
| **刪除 (Deletion)** | $O(1)$ | 只要更改指標指向即可（前提是已找到位置）。 |



---

## 4. Linked List vs. Array

| 特性 | Array | Linked List |
| :--- | :--- | :--- |
| **記憶體分配** | 靜態/連續空間 | 動態/分散空間 |
| **存取速度** | 極快 ($O(1)$) | 慢 ($O(n)$) |
| **插入/刪除** | 慢 (需搬移資料) | 快 (只需改指標) |
| **記憶體使用** | 較省 (僅存資料) | 較費 (需額外儲存指標) |

---

## 5. 程式碼實作範例 (C++)

```cpp
#include <iostream>

// 定義節點結構
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;
    LinkedList() : head(nullptr) {}

    // 在頭部插入新節點 O(1)
    void insertAtFront(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    // 遍歷並列印 O(n)
    void printList() {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "NULL" << std::endl;
    }
};

int main() {
    LinkedList list;
    list.insertAtFront(30);
    list.insertAtFront(20);
    list.insertAtFront(10);
    
    list.printList(); // 輸出: 10 -> 20 -> 30 -> NULL
    return 0;
}
```
---

## 6. 優缺點

### 優點
- 動態大小：不需要預先知道資料量，隨時可以新增節點。
- 高效插入/刪除：在已知位置的情況下，不需要搬移大量元素。

### 缺點
- 搜尋低效：不支援隨機存取，必須從頭遍歷。
- 額外空間：每個資料都要多存一個（或兩個）指標，增加記憶體開銷。
- 對快取不友善：節點分散在記憶體各處，無法利用 CPU Cache 的預取機制。
