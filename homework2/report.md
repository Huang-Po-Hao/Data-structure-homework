# 51115122

作業二

## 解題說明

實作一個Polynomial類別的ADT並實作其私有資料成員，並編寫C++函數來輸入和輸出多項式。輸入和輸出函數應分別多載<<和>>運算子。

### 解題策略

1. Polynomial 類別實作:
   
   使用 Term 類別儲存多項式項，包含係數 (float coef) 和指數 (int exp)。
    
   Polynomial 類別的私有資料成員包括：
   - Term* termArray: 動態陣列，儲存多項式項。
   - int capacity: 陣列容量。
   - int terms: 當前項數。
   
   提供 newTerm 函數動態新增項，容量不足時自動擴展陣列。

   實現建構函數、析構函數和自定義 copy 函數管理記憶體。
   
 2. 多載 << 和 >> 運算子:

    operator>> 使用 std::getline 和 std::istringstream 讀取單行輸入，解析係數和指數對，直到按 Enter 結束。

    operator<< 按指數降序排列項，略過零係數，處理正負號，格式化輸出（如 ax^b + cx^d）。

    特殊處理：指數為 0 不輸出 x，指數為 1 省略 ^1，係數為 1 或 -1 省略係數值。
## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <string>
class Polynomial; 
class Term {
    friend class Polynomial;
    friend std::ostream& operator<<(std::ostream& os, const Term& term);
    friend std::istream& operator>>(std::istream& is, Term& term);
private:
    float coef;
    int exp;
public:
    float getCoef() const { return coef; }
    int getExp() const { return exp; }
};
class Polynomial {
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
    friend std::istream& operator>>(std::istream& is, Polynomial& poly);
private:
    Term* termArray;
    int capacity;
    int terms;
public:
    void copy(Term* target, Term* source, int size) {
        for (int i = 0; i < size; ++i) {
            target[i] = source[i];
        }
    }
    void newTerm(float coef, int exp) {
        if (terms >= capacity) {
            capacity *= 2;
            Term* newArray = new Term[capacity];
            copy(newArray, termArray, terms);
            delete[] termArray;
            termArray = newArray;
            std::cout << "Resized array to capacity: " << capacity << std::endl;
        }
        termArray[terms].coef = coef;
        termArray[terms].exp = exp;
        std::cout << "Added term: " << coef << "x^" << exp << std::endl;
        terms++;
    }
    Polynomial(int initialCapacity = 2) : terms(0) {
        if (initialCapacity <= 0) {
            throw "Invalid capacity";
        }
        capacity = initialCapacity;
        termArray = new Term[capacity];
    }
    ~Polynomial() {
        delete[] termArray;
    }
};
std::istream& operator>>(std::istream& is, Term& term) {
    is >> term.coef >> term.exp;
    return is;
}
std::ostream& operator<<(std::ostream& os, const Term& term) {
    os << term.coef << "x^" << term.exp;
    return os;
}
std::istream& operator>>(std::istream& is, Polynomial& poly) {
    poly.terms = 0;
    std::cout << "Enter terms (coef exp), press Enter to stop:" << std::endl;
    std::string line;
    std::getline(is, line);
    std::istringstream iss(line);
    float coef;
    int exp;
    while (iss >> coef >> exp) {
        std::cout << "Read term: " << coef << "x^" << exp << std::endl;
        poly.newTerm(coef, exp);
    }
    if (iss.eof()) {
        std::cout << "Reached end of input line" << std::endl;
    } else if (iss.fail() && !iss.eof()) {
        std::cout << "Input stream failed" << std::endl;
    }
    return is;
}
std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    std::cout << "Number of terms: " << poly.terms << std::endl;
    std::vector<Term> termsVec(poly.termArray, poly.termArray + poly.terms);
    std::sort(termsVec.begin(), termsVec.end(), [](const Term& a, const Term& b) {
        return a.getExp() > b.getExp();
    });
    bool first = true;
    for (const auto& term : termsVec) {
        float coef = term.getCoef();
        if (coef == 0) continue;
        if (first) {
            first = false;
            if (coef == 1 && term.getExp() != 0) {
                os << (coef < 0 ? "-" : "");
            } else if (coef == -1 && term.getExp() != 0) {
                os << "-";
            } else {
                os << (coef < 0 ? "-" : "") << std::abs(coef);
            }
            int exp = term.getExp();
            if (exp > 0) {
                os << "x";
                if (exp > 1) os << "^" << exp;
            }
        } else {
            if (coef > 0) {
                os << " + ";
                if (coef != 1 || term.getExp() == 0) os << coef;
            } else {
                os << " - ";
                if (coef != -1 || term.getExp() == 0) os << -coef;
            }
            int exp = term.getExp();
            if (exp > 0) {
                os << "x";
                if (exp > 1) os << "^" << exp;
            }
        }
    }
    if (first) {
        os << "0";
    }
    return os;
}
int main() {
    Polynomial polyA;
    std::cin >> polyA;
    std::cout << "Polynomial A: " << polyA << std::endl;
    return 0;
}
```

## 效能分析

1. 時間複雜度： $O(n)$ 
2. 空間複雜度： $O(n)$ 

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數(係數, 指數) | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | 2  0               | 2                   | 2                   |
| 測試二   | 1  1               | x                   | x                   |
| 測試三   | -1  2  2  1        | -x^2 + 2x           | -x^2 + 2x           |
| 測試四   | -1 3 2 2 -1 1 3 0  | -x^3 + 2x^2 - x + 3 | -x^3 + 2x^2 - x + 3 |
| 測試五   | 直接按 Enter        | 0                   | 0                  |

### 結論
- 單項多項式（測試一、測試二）。
- 負係數和多項（測試三、測試四）。
- 空多項式（測試五）。
- 輸入以按 Enter 結束，解析單行輸入，排序確保指數降序，略過零係數項，正負號格式正確，係數 1 或 -1 在非零指數時省略。

## 心得討論

 **設計考量:**
   - 動態陣列 termArray 與 newTerm 函數支援任意項數，自動擴展確保記憶體靈活性。
   - 輸出使用 std::vector 和 std::sort 將指數降冪排列，符合標準多項式表示。
   - 處理特殊情況（如零係數、指數 0 或 1、係數 1 或 -1）確保輸出格式正確。
   - 調試資訊（如 Resized array to capacity 和 Added term）便於追蹤執行過程。
     
透過實作 Polynomial 類別和運算子多載，展示了物件導向程式設計、動態記憶體管理和 C++ 流操作的應用。
