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
- Example output for integers:
  ```
  === Hash Function Observation (C Version) ===

  === Table Size m = 10 ===
  Key     Index
  -----------------
  21      1
  22      2
  ...

  === Table Size m = 11 ===
  Key     Index
  -----------------
  21      10
  22      0
  ...

  === Table Size m = 37 ===
  Key     Index
  -----------------
  21      21
  22      22
  ...

  === Hash Function Observation (C++ Version) ===

  === Table Size m = 10 ===
  Key     Index
  -----------------
  21      1
  22      2
  ...

  === Table Size m = 11 ===
  Key     Index
  -----------------
  21      10
  22      0
  ...

  === Table Size m = 37 ===
  Key     Index
  -----------------
  21      21
  22      22
  ...
  ```

- Example output for strings:
  ```
  === String Hash (m = 10) ===
  Key     Index
  -----------------
  cat     0
  dog     0
  ...

  === String Hash (m = 11) ===
  Key     Index
  -----------------
  cat     0
  dog     0
  ...

  === String Hash (m = 37) ===
  Key     Index
  -----------------
  cat     0
  dog     0
  ...
  ```

- Observations: Outputs align with the analysis, showing better distribution with prime table sizes.
- Example output for integers:
  ```
  Hash table (m=10): [1, 2, 3, 4, 5, 6, 7, 8, 9, 0]
  Hash table (m=11): [10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  Hash table (m=37): [20, 21, 22, 23, 24, 25, 26, 27, 28, 29, ...]
  ```
- Example output for strings:
  ```
  Hash table (m=10): ["cat", "dog", "bat", "cow", "ant", ...]
  Hash table (m=11): ["fox", "cat", "dog", "bat", "cow", ...]
  Hash table (m=37): ["bee", "hen", "pig", "fox", "cat", ...]
  ```
- Observations: Outputs align with the analysis, showing better distribution with prime table sizes.

## Analysis
- Prime vs non-prime `m`: Prime table sizes generally result in better distribution and fewer collisions.
- Patterns or collisions: Non-prime table sizes tend to produce repetitive patterns, leading to more collisions.
- Improvements: Use a prime table size and a well-designed hash function to enhance distribution.

## Reflection
1. Designing hash functions requires balancing simplicity and effectiveness to minimize collisions.
2. Table size significantly impacts the uniformity of the hash distribution, with prime sizes performing better.
3. The design using a prime table size and a linear transformation formula produced the most uniform index sequence.
