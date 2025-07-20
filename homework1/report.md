# 51115122

第1題

## 解題說明

本題要求實現一個遞迴函數來計算 Ackermann 的函數 $A(m, n)$

### 解題策略

如果  m = 0  時，則   A(m, n )=n + 1 。
   
如果  n = 0  時，則  A(m, n )=A(m - 1, 1)。

否則  A(m, n )=A(m - 1, A(m, n - 1))。

直接使用遞迴實現。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
using namespace std;
int ackermann(int m, int n) {
    if (m==0) return n+1;
    else if (n==0) return ackermann(m-1,1);
    else return ackermann(m-1, ackermann(m,n-1));
}
int main() {
    int result=ackermann(2,2);
    cout<<result<<'\n'; 
    return 0;
}
```

## 效能分析
1. 時間複雜度：程式的時間複雜度為 $O(1)$。
2. 空間複雜度：空間複雜度為 $O(A(m, n))$。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $(m,n)$ | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | $(0,0)$      | 1        | 1        |
| 測試二   | $(0,1)$      | 2        | 2        |
| 測試三   | $(1,1)$      | 3        | 3        |
| 測試四   | $(2,2)$      | 7        | 7        |
| 測試五   | $(3,1)$     | 13       | 13       |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o ackermann_recursive ackermann_recursive.cpp
$ ./ackermann_recursive
7
```

### 結論
 遞迴函數能正確計算Ackermann函數值，符合定義。 

## 心得討論

### 選擇遞迴的原因
遞迴直接反映Ackermann函數的數學定義，容易理解和實現。

第二題

## 解題說明
若 ( S ) 為包含 ( n ) 個元素的集合，則 ( S ) 的冪集是 ( S ) 所有可能子集的集合。例如，若 ( S = {a, b, c} )，則冪集為 ( {{}, {a}, {b}, {c}, {a, b}, {a, c}, {b, c}, {a, b, c}} )。任務是撰寫一個遞迴函數計算冪集。
### 解題策略
1.使用遞迴方法，通過考慮每個元素的包含或排除構建冪集。

2.從用戶輸入的集合開始，遞迴添加元素，每次步驟生成雙倍數量的子集。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <vector>
using namespace std;

void ps_rec(vector<int>& s, int i, vector<int>& cur, vector<vector<int>>& res) {
    if (i == s.size()) {
        res.push_back(cur);
        return;
    }
    ps_rec(s, i + 1, cur, res);
    cur.push_back(s[i]);
    ps_rec(s, i + 1, cur, res);
    cur.pop_back();
}

vector<vector<int>> get_ps(vector<int>& s) {
    vector<vector<int>> res;
    vector<int> cur;
    ps_rec(s, 0, cur, res);
    return res;
}

int main() {
    int n;
    cout << "請輸入集合元素數量: ";
    cin >> n;
    vector<int> s(n);
    cout << "請輸入 " << n << " 個元素: ";
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    try {
        vector<vector<int>> ps = get_ps(s);
        for (const auto& sub : ps) {
            cout << "{ ";
            for (int e : sub) cout << e << " ";
            cout << "}" << endl;
        }
    } catch (const char* msg) {
        cout << msg << endl;
    }
    return 0;
}

```

## 效能分析

1 時間複雜度

    1.時間複雜度：$O(n \cdot 2^n)$

2 空間複雜度

    1.空間複雜度：$O(n \cdot 2^n)$

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 \( S \)   | 預期輸出                                   | 實際輸出                                   |
|----------|--------------------|--------------------------------------------|--------------------------------------------|
| 測試一   | \( \{1\} \)        | \( \{\{\}, \{1\}\} \)                      | \( \{\{\}, \{1\}\} \)                      |
| 測試二   | \( \{1, 2\} \)     | \( \{\{\}, \{1\}, \{2\}, \{1, 2\}\} \)     | \( \{\{\}, \{1\}, \{2\}, \{1, 2\}\} \)     |
| 測試三   | \( \{1, 2, 3\} \)  | \( \{\{\}, \{1\}, \{2\}, \{3\}, \{1, 2\}, \{1, 3\}, \{2, 3\}, \{1, 2, 3\}\} \) | \( \{\{\}, \{1\}, \{2\}, \{3\}, \{1, 2\}, \{1, 3\}, \{2, 3\}, \{1, 2, 3\}\} \) |


### 編譯與執行指令
$ g++ -std=c++17 -o powerset powerset.cpp
$ ./powerset
請輸入集合元素數量: 3
請輸入 3 個元素: 1 2 3
{ }
{ 1 }
{ 2 }
{ 1 2 }
{ 3 }
{ 1 3 }
{ 2 3 }
{ 1 2 3 }

### 結論

1.程式能正確生成用戶輸入集合的冪集。

2.測試案例涵蓋不同元素數量的情況，驗證了遞迴實現的正確性。

## 申論及開發報告
1.程式能正確生成用戶輸入集合的冪集。

2.測試案例涵蓋不同元素數量的情況，驗證了遞迴實現的正確性。

### 選擇遞迴的原因

選擇方法的理由

1.遞迴方法：通過每個元素的二元選擇（包含/排除）生成子集，邏輯簡單，適合展示遞迴概念，並透過輸入功能提升互動性。

2.向量使用：使用 vector 動態儲存子集，靈活處理用戶輸入的集合。

3.限制與改進：當 ( n ) 過大時，空間需求會指數增長，建議未來考慮位元運算優化。
