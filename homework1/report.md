# 51115122

第1題

## 解題說明

題目要求實現一個遞迴函數來計算Ackermann函數  A(m, n) ，並進一步提供一個非遞迴算法來計算該函數。

### 解題策略

1. **遞迴函數**:
   
   如果  m = 0  時，則   A(m, n )=n + 1 。
   
   如果  n = 0  時，則  A(m, n )=A(m - 1, 1)。

   否則  A(m, n )=A(m - 1, A(m, n - 1))。

   直接使用遞迴實現。

2. **非遞迴算法**:
   
    為避免深層遞迴導致的堆疊溢出，設計一個使用堆疊或循環的疊代算法。
   
    將計算分解為逐步更新 \( m \) 和 \( n \) 的操作。

## 程式實作

以下為主要程式碼：

### 遞迴

```cpp
#include <iostream>
using namespace std;
int ackermann(int m, int n) {
    if (m==0) return n+1;
    else if (n==0) return ackermann(m-1,1);
    else return ackermann(m-1, ackermann(m,n-1));
}
int main() {
    int m, n;
    cin >> m >> n;
    int result = ackermann(m, n);
    cout << result << '\n';
    return 0;
}
```

### 非遞迴

```cpp
#include <iostream>
using namespace std;

int ackermann(int m, int n) {
    struct Call { int m, n; };
    Call stack[100000]; 
    int top = -1;
    stack[++top] = {m, n};
    
    while (top >= 0) {
        Call current = stack[top--];
        m = current.m;
        n = current.n;
        
        if (m == 0) {
            if (top == -1) {
                return n + 1;
            }
            stack[top].n = n + 1;
        } else if (n == 0) {
            stack[++top] = {m - 1, 1};
        } else {
            stack[++top] = {m - 1, -1}; 
            stack[++top] = {m, n - 1};
        }
    }
    return n; 
}
int main() {
    int m, n;
    cin >> m >> n;
    int result = ackermann(m, n);
    cout << result << '\n';
    return 0;
}
```

## 效能分析

1.**時間複雜度:**

遞迴: 程式的時間複雜度為 $O(1)$。

非遞迴: 使用堆疊模擬，時間複雜度依賴於 ( m ) 和 ( n ) 的值，約為 ( O(2^{m+n}) )。

2.**空間複雜度:**

遞迴: 空間複雜度為 $O(A(m, n))$。

非遞迴: ( O(m \cdot n) ) 因堆疊使用。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $(m,n)$ | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | $(0,0)$      | 1        | 1        |
| 測試二   | $(0,1)$      | 2        | 2        |
| 測試三   | $(1,1)$      | 3        | 3        |
| 測試四   | $(2,1)$      | 5        | 5        |
| 測試五   | $(2,2)$      | 7        | 7        |
| 測試六   | $(3,1)$      | 13       | 13       |
| 測試七   | $(3,2)$      | 29       | 29       |
| 測試八   | $(3,3)$      | 61       | 61       |

### 結論
 遞迴函數能正確計算Ackermann函數值，符合定義。 

 非遞迴算法通過堆疊模擬遞迴，成功計算相同結果。

## 心得討論

### 選擇遞迴的原因
遞迴直接反映Ackermann函數的數學定義，容易理解和實現。

### 轉向非遞迴的原因

1. **效能與穩定性:**
   
     遞迴可能因大 ( m ) 或 ( n ) 導致堆疊溢出，非遞迴版本通過堆疊管理避免此問題。

     疊代實現更適合實際應用，特別是當 ( m ) 和 ( n ) 較大時。

3. **資源控制:**
   非遞迴算法允許手動管理記憶體和計算步驟，適應資源受限環境。

透過遞迴和非遞迴兩種實現，展示了Ackermann函數的計算方法。遞迴適合理論學習，非遞迴則更實用於工程應用。
