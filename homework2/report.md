# 51115122

作業二

## 解題說明

題目要求實作一個Polynomial類別的ADT並實作其私有資料成員，並編寫C++函數來輸入和輸出多項式。輸入和輸出函數應分別多載<<和>>運算子。

### 解題策略

1. Polynomial 類別實作:
   
   根據ADT，實作Polynomial類別的必要功能，例如建構函數、複製建構函數、析構函數，以及其他操作(如加法、乘法）。
    
   假設私有資料成員包含多項式的係數陣列和最高次數，例如 double* coefficients 和 int degree，用來儲存多項式的係數和最高次數。
   
 2. 多載 << 和 >> 運算子:

    多載輸出運算子 << 以格式化輸出多項式，例如以 ax^n + bx^(n-1) + ... + c 的形式。

    多載輸入運算子 >> 以從輸入流讀取多項式的次數和係數。

    確保輸入和輸出格式清晰且符合一般多項式表示法。

3. 假設的資料結構:
   
   - 私有資料成員包含：
     
       double* coefficients: 動態陣列，儲存各次項的係數。
     
       int degree: 多項式的最高次數。
   - 重點在於輸入和輸出功能的實作。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <cmath>
using namespace std;
class Polynomial {
private:
    double* coefficients; 
    int degree;         
public:
    Polynomial(int deg = 0) : degree(deg) {
        coefficients = new double[deg + 1];
        for (int i = 0; i <= deg; i++) {
            coefficients[i] = 0.0;
        }
    }
    Polynomial(const Polynomial& other) : degree(other.degree) {
        coefficients = new double[degree + 1];
        for (int i = 0; i <= degree; i++) {
            coefficients[i] = other.coefficients[i];
        }
    }
    ~Polynomial() {
        delete[] coefficients;
    }
    friend istream& operator>>(istream& in, Polynomial& poly) {
        cout << "Enter degree of polynomial: ";
        in >> poly.degree;
        delete[] poly.coefficients; 
        poly.coefficients = new double[poly.degree + 1];
        cout << "Enter coefficients from highest to lowest degree: ";
        for (int i = poly.degree; i >= 0; i--) {
            in >> poly.coefficients[i];
        }
        return in;
    }
    friend ostream& operator<<(ostream& out, const Polynomial& poly) {
        bool first = true;
        for (int i = poly.degree; i >= 0; i--) {
            if (poly.coefficients[i] != 0) {
                if (!first && poly.coefficients[i] > 0) {
                    out << " + ";
                }
                if (poly.coefficients[i] < 0) {
                    out << " - ";
                }
                if (abs(poly.coefficients[i]) != 1 || i == 0) {
                    out << abs(poly.coefficients[i]);
                }
                if (i > 0) {
                    out << "x";
                    if (i > 1) {
                        out << "^" << i;
                    }
                }
                first = false;
            }
        }
        if (first) { 
            out << "0";
        }
        return out;
    }
};
int main() {
    Polynomial poly;
    cin >> poly; 
    cout << "Polynomial: " << poly << endl; 
    return 0;
}
```

## 效能分析

1. 時間複雜度： $O(n)$ 
2. 空間複雜度： $O(n)$ 

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數(次數, 係數) | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | 次數: 0, 係數: [2]          | 2            | 2            |
| 測試二   | 次數: 1, 係數: [3,0]        | 3x           | 3x           |
| 測試三   | 次數: 2, 係數: [1,-2,0]     | x^2 - 2x     | x^2 - 2x     |
| 測試四   | 次數: 3, 係數: [2,0,-1,3]   | 2x^3 - x + 3 | 2x^3 - x + 3 |
| 測試五   | 次數: 2, 係數: [0,0,0]      | 0            | 0            |

### 結論
- 程式正確實現了Polynomial類別，並根據私有資料成員（係數陣列和次數）進行設計。
- 重載的 << 和 >> 運算子能正確處理多項式的輸入和輸出，格式清晰且符合數學表示法。
- 測試案例涵蓋了常數項、線性多項式、高次多項式以及全零多項式，驗證了程式的正確性。

