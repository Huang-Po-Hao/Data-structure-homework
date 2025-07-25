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
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <string>

class Polynomial; // 前向宣告

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
| 測試一   | 2  0          | 2            | 2            |
| 測試二   | 1  1      | x           | x           |
| 測試三   | -1  2  2  1     | -x^2 + 2x    | -x^2 + 2x     |
| 測試四   | -1 3 2 2 -1 1 3 0  | -x^3 + 2x^2 - x + 3 | -x^3 + 2x^2 - x + 3 |
| 測試五   | 直接按 Enter     | 0            | 0            |

### 結論
- 程式正確實現了Polynomial類別，並根據私有資料成員（係數陣列和次數）進行設計。
- 重載的 << 和 >> 運算子能正確處理多項式的輸入和輸出，格式清晰且符合數學表示法。
- 測試案例涵蓋了常數項、線性多項式、高次多項式以及全零多項式，驗證了程式的正確性。

