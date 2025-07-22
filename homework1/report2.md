# 51115122

第2題

## 解題說明

題目要求實現一個遞迴函式，計算集合 $ S $ 的所有可能子集（即幂集，powerset）。幂集包含集合 $ S $ 的空集以及所有可能的非空子集。

### 解題策略

1.使用遞迴函式將問題分解：對於集合 $ S $，移除最後一個元素，計算剩餘子集，並為每個子集添加或不添加該元素以生成完整幂集。

2.基本情況：當集合為空時，返回包含空集的幂集。

3.主程式呼叫遞迴函式，並輸出結果。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <vector>
using namespace std;

void powerset(vector<char>& S, vector<vector<char>>& result, vector<char> current, int index) {
    // 基本情況：當索引到達集合末尾時，添加當前子集
    if (index == S.size()) {
        result.push_back(current);
        return;
    }
    // 不包含當前元素
    powerset(S, result, current, index + 1);
    // 包含當前元素
    current.push_back(S[index]);
    powerset(S, result, current, index + 1);
}

vector<vector<char>> powerset(vector<char> S) {
    vector<vector<char>> result;
    vector<char> current;
    powerset(S, result, current, 0);
    return result;
}

int main() {
    vector<char> S = {'a', 'b', 'c'};
    vector<vector<char>> result = powerset(S);
    for (const auto& subset : result) {
        cout << "{ ";
        for (char c : subset) {
            cout << c << " ";
        }
        cout << "}" << endl;
    }
    return 0;
}
```

## 效能分析

1.時間複雜度:
程式的時間複雜度為 $O(1)$。

2.空間複雜度:
空間複雜度為 $O(A(m, n))$。

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
