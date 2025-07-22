# 51115122

第2題

## 解題說明

題目要求實現一個遞迴函式，計算集合S的所有可能子集。幂集包含集合S的空集以及所有可能的非空子集。

### 解題策略

1.使用遞迴函式將問題分解：對於集合S，移除最後一個元素，計算剩餘子集，並為每個子集添加或不添加該元素以生成完整幂集。

2.基本情況：當集合為空時，返回包含空集的幂集。

3.主程式呼叫遞迴函式，並輸出結果。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <vector>
using namespace std;

void powerset(vector<char>& S, vector<vector<char>>& result, vector<char> current, int index) {
    if (index == S.size()) {
        result.push_back(current);
        return;
    }
    powerset(S, result, current, index + 1);
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
 $O(2^n)$。

2.空間複雜度:
 $O(2^n)$。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $S$ | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | $S=${}        | {}        | {}       |
| 測試二   | $S=${'a'}     | {},{a}    | {},{a}   | 
| 測試三   | $S=${'a','b'} | {},{a},{b},{a,b}     | {},{a},{b},{a,b}|
| 測試四   | $S=${'a','b','c'} | {},{a},{b},{c},{a,b},{a,c},{b,c},{a,b,c}|{},{c},{b},{b,c},{a},{a,c},{a,b},{a,b,c}         |

### 結論
 程式能正確計算集合S的所有子集。

 測試案例涵蓋了空集、單元素集和多元素集，驗證程式的正確性。

## 心得討論

1. **程式邏輯簡單直觀:**
   
    遞迴方法通過為每個元素決定是否包含，清楚表達幂集的生成過程。例如，對於 $S = ${a, b, c}，遞迴逐一處理每個元素，生成所有組合。

2. **遞迴的語意清晰:**

   每次遞迴呼叫處理一個元素，生成包含該元素和不包含該元素的子集，逐層擴展最終結果，符合問題的遞推性質。

雖然遞迴實現直觀且符合問題的本質，但當n 較大時，空間複雜度 $O(2^n)$可能導致記憶體使用問題。
