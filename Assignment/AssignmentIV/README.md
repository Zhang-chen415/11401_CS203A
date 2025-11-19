# Homework Assignment IV: Hash Function Design & Observation (C/C++ Version)

This assignment focuses on the design and observation of hash functions using C/C++. 
Students are expected to implement and analyze the behavior of hash functions, 
evaluate their efficiency, and understand their applications in computer science.

Developer: 張新誠
Email: s1131435@mail.yzu.edu.tw  

## My Hash Function
### Integer Keys 
- Formula / pseudocode:
  ```text
  1. 錯誤檢查：若 m <= 0，顯示錯誤並回傳 0
  2. 平方 ：long long square = key * key
  3. 取中 ：square = square / 10 (移除個位數)
  4. 取餘 ：return square % m
  ```
- Rationale: 本實作採用平方取中法的變體。
    - 平方擴散：先將 Key 平方 ($key^2$)，利用乘法將數值差異擴大，避免連續整數產生連續的 Hash 值。
    - 移除末位：將平方數除以 10 (/= 10)，目的是移除變化較規律的末位數字，保留較具隨機性的中間位數。
    - 減少碰撞：相較於直接取餘數 ($k \% m$)，此方法能有效打散規律性數據（如 21, 22...）造成的碰撞。此外，程式包含對 $m \le 0$ 的錯誤檢查，確保執行穩健性。

### Non-integer Keys
- Formula / pseudocode:
  ```text
  1. 錯誤檢查：若 m <= 0 或字串為空，顯示錯誤並回傳 0
  2. 數值轉換：hash = 加總所有字元的 ASCII 碼
  3. 平方 ：long long square = hash * hash
  4. 取中 ：square = square / 10 (移除個位數)
  5. 取餘 ：return square % m
  ```
- Rationale: 針對字串鍵值，結合了 加法雜湊 與 類似餘平方取中法的方法。
  - 轉換數值：首先計算字串所有字元的 ASCII 總和。
  - 消除重組碰撞：單純的加法雜湊容易在字母重組時（例如 "abc" 與 "cba" 總和相同）產生碰撞。透過將總和 平方 ($Sum^2$) 並 除以 10，能放大這些總和的特徵，使內容相似的字串也能映射到不同的索引。
  - 輸入驗證：程式加入了空字串檢查，防止無效輸入導致錯誤。

## Experimental Setup
- Table sizes tested (m): 10, 11, 37
- Test dataset:
  - Integers: 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60
  - Strings: "cat", "dog", "bat", "cow", "ant", "owl", "bee", "hen", "pig", "fox"
- Compiler: G++
- Standard: C++23

## Results
### Integer Keys Comparison (整數雜湊比較)

**測試數據 (Key)**: 21-30, 51-60

| Table Size (m) | 方法 | 部分範例 | 觀察 |
| :--- | :--- | :--- | :--- |
| **$m = 10$** | **傳統除法** | `1, 2, 3, 4, 5...` | **嚴重規律**：Key 連續增加，Index 也連續增加，完全沒有打散效果。 |
| | **平方取中** | `4, 8, 2, 7, 2...` | **成功打散**：雖然輸入連續，但 Index 呈現跳躍分佈，消除了線性規律。 |
| **$m = 11$** | **傳統除法** | `10, 0, 1, 2...` | **尚可**：依賴質數 $m$ 來分散，但仍保有連續性。 |
| | **平方取中** | `0, 4, 8, 2...` | **更佳**：結合質數與平方運算，分佈更加隨機。 |
| **$m = 37$** | **傳統除法** | `21, 22, 23...` | **線性分佈**：Index 依然隨著 Key 線性增加。 |
| | **平方取中** | `7, 11, 15, 20...` | **高度分散**：Index 分佈範圍廣且無明顯線性關係。 |

### String Keys Comparison (字串雜湊比較)

**測試數據 (Key)**: "cat", "dog", "bat", "cow", "ant", "owl", "bee", "hen", "pig", "fox"

| Table Size (m) | 方法 (Method) | Collision Example (碰撞範例) | 觀察 (Observation) |
| :--- | :--- | :--- | :--- |
| **$m = 10$** | **傳統除法** | `bee` (0), `pig` (0) | 容易在 $m$ 較小時發生碰撞。 |
| | **平方取中** | `bee` (0), `pig` (0) | 在 $m$ 極小時，雖然仍有碰撞，但整體分佈位置改變 (例如 `dog` 從 4 變 9)。 |
| **$m = 37$** | **傳統除法** | (無明顯碰撞) | 大 Table Size 下兩者表現皆不錯。 |
| | **平方取中** | (無明顯碰撞) | 索引分佈更為跳躍，例如 `cow` 從 33 變 20。 |

---

## Compilation, Build, Execution, and Output

### Compilation
- The project uses a comprehensive Makefile that builds both C and C++ versions with proper flags:
  ```bash
  # Build both C and C++ versions
  make all
  
  # Build only C version
  make c
  
  # Build only C++ version
  make cxx
  ```

### Manual Compilation (if needed)
- Command for C:
  ```bash
  gcc -std=c23 -Wall -Wextra -Wpedantic -g -o C/hash_function C/main.c C/hash_fn.c
  ```
- Command for C++:
  ```bash
  g++ -std=c++23 -Wall -Wextra -Wpedantic -g -o CXX/hash_function_cpp CXX/main.cpp CXX/hash_fn.cpp
  ```

### Clean Build Files
- Remove all compiled files:
  ```bash
  make clean
  ```

### Execution
- Run the compiled binary:
  ```bash
  ./hash_function
  ```
  or
  ```bash
  ./hash_function_cpp
  ```

### Result Snapshot

- output for integers:
```
=== Hash Function Observation (C++ Version) ===

=== Table Size m = 10 ===
Key     Index
-----------------
21      4
22      8
23      2
24      7
25      2
26      7
27      2
28      8
29      4
30      0
51      0
52      0
53      0
54      1
55      2
56      3
57      4
58      6
59      8
60      0

=== Table Size m = 11 ===
Key     Index
-----------------
21      0
22      4
23      8
24      2
25      7
26      1
27      6
28      1
29      7
30      2
51      7
52      6
53      5
54      5
55      5
56      5
57      5
58      6
59      7
60      8

=== Table Size m = 37 ===
Key     Index
-----------------
21      7
22      11
23      15
24      20
25      25
26      30
27      35
28      4
29      10
30      16
51      1
52      11
53      21
54      32
55      6
56      17
57      28
58      3
59      15
60      27
```
- output for strings
```

=== String Hash (m = 10) ===
Key     Index
-----------------
cat     4
dog     9
bat     2
cow     4
ant     2
owl     4
bee     0
hen     2
pig     0
fox     8

=== String Hash (m = 11) ===
Key     Index
-----------------
cat     10
dog     3
bat     3
cow     0
ant     4
owl     6
bee     2
hen     0
pig     10
fox     0

=== String Hash (m = 37) ===
Key     Index
-----------------
cat     3
dog     17
bat     15
cow     20
ant     35
owl     28
bee     9
hen     6
pig     28
fox     25
```

- Example output for integers:
  ```
  Hash table (m=10): [4, 8, 2, 7, 2, 7, 2, 8, 4, 0]
  Hash table (m=11): [0, 4, 8, 2, 7, 1, 6, 1, 7, 2]
  Hash table (m=37): [7, 11, 15, 20, 25, 30, 35, 4, 10, 16, ...]
  ```
- Example output for strings:
  ```
  Hash table (m=10): ["cat"(4), "dog"(9), "bat"(2), "cow"(4), "ant"(2)...]
  Hash table (m=11): ["cat"(10), "dog"(3), "bat"(3), "cow"(0), "ant"(4)...]
  Hash table (m=37): ["cat"(3), "dog"(17), "bat"(15), "cow"(20), "ant"(35)...]
  ```
- Observations: 輸出結果與分析一致。不同於傳統除法法產生連續的規律（如 1, 2, 3...），平方取中法 成功地將索引打散（如 4, 8, 2...），即使在 Table Size 較小的情況下，也能有效破壞連續 Key 的線性規律。

## Analysis
1.  **消除線性規律**:
    * 在 **傳統除法** ($k \% m$) 中，若 $m=10$，輸入 `21, 22, 23` 會直接映射為 `1, 2, 3`。這種線性關係在 Hash Table 中容易導致叢集。
    * 使用 **平方取中法** 後，同樣輸入 `21, 22, 23` 被映射為 `4, 8, 2`。這證明了平方運算成功破壞了輸入資料的線性結構。

2.  **高位資訊的利用**:
    * 整數測試中的 `51, 52, 53` 在傳統除法 ($m=10$) 下映射為 `1, 2, 3`，與 `21, 22, 23` 發生完全相同的碰撞模式。
    * 在平方取中法下，`51, 52, 53` 被映射為 `0, 0, 0` (雖有碰撞但模式改變)。這顯示高位數字 (`5` vs `2`) 確實影響了最終結果，而非僅依賴個位數。

3.  **質數的影響**:
    * 實驗結果再次證實，**質數 (Prime Number)** (如 $m=11, 37$) 能顯著提升雜湊的分佈均勻度。即便演算法僅使用簡單的除法，質數也能提供基本的保護；且若配合平方取中法，能達到更佳的亂度。

## Reflection
1. **設計**：設計雜湊函數時，需要在運算複雜度與碰撞最小化之間取得平衡。
2. **Table Size 的影響**：Table Size 對雜湊分佈的均勻性有顯著影響，實驗證實質數的大小 (如 11, 37) 能提供較好的分佈效果。
3. **演算法成效**：本次採用的 **平方取中法 (Mid-Square Method)** 成功解決了連續鍵值產生連續索引的問題。相較於單純的線性除法，非線性的平方運算能更有效地打散數據，避免叢集發生。
