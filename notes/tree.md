# Tree (樹)

樹（Tree）是電腦科學中最重要的**非線性（Non-linear）**資料結構之一，用於表示具有層次關係（Hierarchical）的數據，例如檔案系統、組織架構圖等。

---

## 1. 樹的基本概念 (General Tree)

樹是由節點（Nodes）與邊（Edges）組成的集合。最頂端的節點稱為**根節點（Root）**。

### 核心術語


* **Root (根節點)**：唯一的頂層節點，沒有父節點。
* **Node (節點)**：存儲資料的基本單位。
* **Edge (邊)**：連接父子節點的線段。
* **Leaf (葉節點)**：沒有子節點的末端節點。
* **Parent/Child (父節點/子節點)**：具有直接相連關係的上下層節點。
* **Sibling (兄弟節點)**：擁有相同父節點的節點。
* **Height (高度)**：從該節點到最遠葉節點的最長路徑。
* **Depth (深度)**：從根節點到該節點的路徑長度。

---

## 2. 樹的遍歷 (Tree Traversal)

走訪樹中節點的順序對演算法結果至關重要，主要分為：

### 深度優先搜尋 (DFS)
| 遍歷方式 | 順序規則 | 應用場景 |
| :--- | :--- | :--- |
| **前序 (Pre-order)** | 根 → 左 → 右 | 複製樹、表示目錄結構 |
| **中序 (In-order)** | 左 → 根 → 右 | **在 BST 中可得到排序數列** |
| **後序 (Post-order)** | 左 → 右 → 根 | 刪除樹、計算子目錄大小 |



### 廣度優先搜尋 (BFS)
* **層序遍歷 (Level-order)**：逐層由上而下、由左至右訪問節點。

---

## 3. Binary Search Tree (BST, 二元搜尋樹)

**BST** 是一種特殊的二元樹，它透過嚴格的排序規則讓搜尋與插入達到極高的效率。

### BST 的定義性質
1.  **左子樹**所有節點的值都 **小於** 根節點的值。
2.  **右子樹**所有節點的值都 **大於** 根節點的值。
3.  左右子樹也必須各自符合上述兩條性質。



### 時間複雜度分析
在資料結構中，效能高度依賴於**樹的高度 ($h$)**：

| 操作 | 平均情況 (平衡時) | 最壞情況 (歪斜時) |
| :--- | :---: | :---: |
| **搜尋 (Search)** | $O(\log n)$ | $O(n)$ |
| **插入 (Insertion)** | $O(\log n)$ | $O(n)$ |
| **刪除 (Deletion)** | $O(\log n)$ | $O(n)$ |

> **提示**：當資料按順序插入時，BST 會退化成一條直線（歪斜樹），效率變低。實務中會使用「平衡樹」（如 AVL Tree 或紅黑樹）來確保高度維持在 $\log n$。

---

## 4. 程式碼實作 (C++)

```cpp
#include <iostream>

struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
public:
    Node* root;
    BST() : root(nullptr) {}

    // 插入節點 O(log n)
    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);
        return node;
    }

    // 中序遍歷 (輸出排序後的結果)
    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }
};
```
---

## 5. 總結與應用

- 優勢：動態資料維護且搜尋速度快（優於 Linked List，且比 Array 更容易插入刪除）。
- 應用：資料庫索引、檔案管理系統、優先權佇列（Heap 是樹的一種變體）。
