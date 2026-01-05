# Heap (堆積) - 優先權管理專家

堆積（Heap）是一種特殊的**完全二元樹（Complete Binary Tree）**。它最核心的特性在於「父節點與子節點之間存在固定的排序關係」，這使得它非常適合用來快速找出集合中的最大值或最小值。

---

## 1. Heap 的兩大類型

根據父節點與子節點的關係，Heap 分為以下兩類：

### 最大堆積 (Max Heap)
* **規則**：每個父節點的值都 **大於或等於** 其子節點的值。
* **結果**：根節點（Root）永遠是整棵樹中的**最大值**。

### 最小堆積 (Min Heap)
* **規則**：每個父節點的值都 **小於或等於** 其子節點的值。
* **結果**：根節點（Root）永遠是整棵樹中的**最小值**。



---

## 2. 物理實作：為什麼用陣列 (Array)？

雖然 Heap 邏輯上是一棵樹，但因為它是**完全二元樹**（除了最後一層外，每一層都是滿的，且最後一層節點由左向右靠），我們通常直接使用**陣列**來儲存，這樣最節省空間。

若根節點索引為 `0`，則對於任意索引為 `i` 的節點：
* **左子節點索引**：`2 * i + 1`
* **右子節點索引**：`2 * i + 2`
* **父節點索引**：`(i - 1) / 2` (整數除法)

[Image showing Array representation of a Binary Heap]

---

## 3. 核心操作與複雜度

Heap 的所有操作都旨在維持「堆積性質」（Heap Property）。

| 操作 | 時間複雜度 | 描述 |
| :--- | :---: | :--- |
| **Get Top** | $O(1)$ | 直接回傳根節點的值（最大或最小）。 |
| **Insertion (Push)** | $O(\log n)$ | 將新元素放在末尾，並向上進行「向上調整 (Sift Up)」。 |
| **Extraction (Pop)** | $O(\log n)$ | 移除根節點，將末尾元素移至根部，並向下進行「向下調整 (Sift Down)」。 |
| **Heapify** | $O(n)$ | 將一個隨機陣列轉換成堆積。 |

---

## 4. 程式碼實作範例 (C++ - Max Heap)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

class MaxHeap {
private:
    std::vector<int> heap;

    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] > heap[parent]) {
                std::swap(heap[index], heap[parent]);
                index = parent;
            } else break;
        }
    }

    void siftDown(int index) {
        int size = heap.size();
        while (2 * index + 1 < size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = left;
            if (right < size && heap[right] > heap[left]) largest = right;
            
            if (heap[largest] > heap[index]) {
                std::swap(heap[index], heap[largest]);
                index = largest;
            } else break;
        }
    }

public:
    void push(int val) {
        heap.push_back(val);
        siftUp(heap.size() - 1);
    }

    int pop() {
        int top = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        siftDown(0);
        return top;
    }

    int peek() { return heap[0]; }
};
```

---
## 5. 堆積的經典應用

- 優先權佇列 (Priority Queue)：系統排程、網路封包處理，優先處理重要等級較高的任務。
- 堆積排序 (Heap Sort)：一種效率為 $O(n \log n)$ 的原地排序演算法。
- Top K 問題：在數百萬筆資料中，快速找出最大或最小的前 K 個元素（例如：熱門關鍵字排行榜）。
- 圖論演算法優化：如 Dijkstra 演算法中，使用 Min-Heap 快速找到權重最小的邊。
