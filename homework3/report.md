# 51115122

作業三

## 解題說明

題目要求開發一個 C++ 類別 Polynomial 來表示並操作單變數整數係數多項式，使用帶頭結點的循環鏈表。每個多項式項由係數 (coef) 和指數 (exp) 表示，並包含以下功能：
- 使用循環鏈表表示多項式，頭結點用於鏈表管理。
- 提供可用空間列表以高效刪除多項式。
- 實現多項式的輸入輸出、複製、賦值、加減乘運算及評估。

### 解題策略
1. 類別設計:
- 定義 Term 結構，包含 coef (整數係數)、exp (整數指數) 及 link (指向下一個節點的指標)。
- Polynomial 類別使用循環鏈表，header 作為頭結點，available 管理釋放的節點。
2. 函數實現:
- (a) operator>>: 從輸入流讀取項數 n 及 n 對 coef 和 exp，構建循環鏈表。
- (b) operator<<: 將循環鏈表轉為外部表示並輸出，略過零係數項。
- (c) 複製建構函數: 複製輸入多項式的鏈表結構。
- (d) 賦值運算子: 將多項式賦值給當前實例。
- (e) 析構函數: 釋放所有節點並歸還至可用空間列表。
- (f) 加法運算子: 計算兩個多項式之和。
- (g) 減法運算子: 計算兩個多項式之差。
- (h) 乘法運算子: 計算兩個多項式之積。
- (i) 評估函數: 計算多項式在指定 x 處的值。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <cmath>

class Term {
    friend class Polynomial;
    int coef;
    int exp;
    Term* link;
};
class Polynomial {
private:
    Term* header;
    Term* available;
    Term* allocateTerm() {
        if (available) {
            Term* temp = available;
            available = available->link;
            return temp;
        }
        return new Term;
    }
    void deallocateTerm(Term* term) {
        term->link = available;
        available = term;
    }
public:
    Polynomial() {
        header = new Term;
        header->link = header;
        available = nullptr;
    }
    ~Polynomial() {
        Term* current = header->link;
        while (current != header) {
            Term* temp = current;
            current = current->link;
            deallocateTerm(temp);
        }
        delete header;
    }
    friend std::istream& operator>>(std::istream& is, Polynomial& p) {
        p.~Polynomial();
        p.header = new Term;
        p.header->link = p.header;
        p.available = nullptr;
        int n;
        if (!(is >> n)) return is; 
        if (n == 0) return is;
        Term* current = p.header;
        for (int i = 0; i < n; ++i) {
            int c, e;
            if (!(is >> c >> e)) {
                std::cerr << "Error: Insufficient data for " << n << " terms." << std::endl;
                return is;
            }
            Term* newTerm = p.allocateTerm();
            newTerm->coef = c;
            newTerm->exp = e;
            newTerm->link = p.header;
            current->link = newTerm;
            current = newTerm;
        }
        current->link = p.header;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
        Term* current = p.header->link;
        bool first = true;
        bool hasTerms = false;
        while (current != p.header) {
            if (current->coef == 0) {
                current = current->link;
                continue;
            }
            hasTerms = true;
            if (!first && current->coef > 0) os << " + ";
            if (current->coef < 0) os << " - ";
            int absCoef = std::abs(current->coef);
            if (absCoef != 1 || current->exp == 0) os << absCoef;
            if (current->exp > 0) os << "x";
            if (current->exp > 1) os << "^" << current->exp;
            first = false;
            current = current->link;
        }
        if (!hasTerms) os << "0";
        return os;
    }
    Polynomial(const Polynomial& a) {
        header = new Term;
        header->link = header;
        available = nullptr;
        Term* src = a.header->link;
        Term* dest = header;
        while (src != a.header) {
            Term* newTerm = allocateTerm();
            newTerm->coef = src->coef;
            newTerm->exp = src->exp;
            dest->link = newTerm;
            dest = newTerm;
            src = src->link;
        }
        dest->link = header;
    }
    const Polynomial& operator=(const Polynomial& a) {
        if (this != &a) {
            this->~Polynomial();
            new (this) Polynomial(a);
        }
        return *this;
    }
    Polynomial operator+(const Polynomial& b) const {
        Polynomial result;
        Term* aPtr = header->link;
        Term* bPtr = b.header->link;
        Term* resultTail = result.header;
        while (aPtr != header || bPtr != b.header) {
            Term* newTerm = result.allocateTerm();
            if (aPtr == header) {
                newTerm->coef = bPtr->coef;
                newTerm->exp = bPtr->exp;
                bPtr = bPtr->link;
            } else if (bPtr == b.header || aPtr->exp > bPtr->exp) {
                newTerm->coef = aPtr->coef;
                newTerm->exp = aPtr->exp;
                aPtr = aPtr->link;
            } else if (aPtr->exp < bPtr->exp) {
                newTerm->coef = bPtr->coef;
                newTerm->exp = bPtr->exp;
                bPtr = bPtr->link;
            } else {
                newTerm->coef = aPtr->coef + bPtr->coef;
                newTerm->exp = aPtr->exp;
                aPtr = aPtr->link;
                bPtr = bPtr->link;
            }
            if (newTerm->coef != 0) {
                resultTail->link = newTerm;
                resultTail = newTerm;
            } else {
                result.deallocateTerm(newTerm);
            }
        }
        resultTail->link = result.header;
        return result;
    }
    Polynomial operator-(const Polynomial& b) const {
        Polynomial result;
        Term* aPtr = header->link;
        Term* bPtr = b.header->link;
        Term* resultTail = result.header;
        while (aPtr != header || bPtr != b.header) {
            Term* newTerm = result.allocateTerm();
            if (aPtr == header) {
                newTerm->coef = -bPtr->coef;
                newTerm->exp = bPtr->exp;
                bPtr = bPtr->link;
            } else if (bPtr == b.header || aPtr->exp > bPtr->exp) {
                newTerm->coef = aPtr->coef;
                newTerm->exp = aPtr->exp;
                aPtr = aPtr->link;
            } else if (aPtr->exp < bPtr->exp) {
                newTerm->coef = -bPtr->coef;
                newTerm->exp = bPtr->exp;
                bPtr = bPtr->link;
            } else {
                newTerm->coef = aPtr->coef - bPtr->coef;
                newTerm->exp = aPtr->exp;
                aPtr = aPtr->link;
                bPtr = bPtr->link;
            }
            if (newTerm->coef != 0) {
                resultTail->link = newTerm;
                resultTail = newTerm;
            } else {
                result.deallocateTerm(newTerm);
            }
        }
        resultTail->link = result.header;
        return result;
    }
    Polynomial operator*(const Polynomial& b) const {
        Polynomial result;
        Term* aPtr = header->link;
        while (aPtr != header) {
            Term* bPtr = b.header->link;
            while (bPtr != b.header) {
                Term* newTerm = result.allocateTerm();
                newTerm->coef = aPtr->coef * bPtr->coef;
                newTerm->exp = aPtr->exp + bPtr->exp;
                Term* resultPtr = result.header->link;
                Term* prev = result.header;
                while (resultPtr != result.header) {
                    if (resultPtr->exp == newTerm->exp) {
                        resultPtr->coef += newTerm->coef;
                        result.deallocateTerm(newTerm);
                        newTerm = nullptr;
                        break;
                    }
                    prev = resultPtr;
                    resultPtr = resultPtr->link;
                }
                if (newTerm && newTerm->coef != 0) {
                    prev->link = newTerm;
                    newTerm->link = result.header;
                } else if (newTerm) {
                    result.deallocateTerm(newTerm);
                }
                bPtr = bPtr->link;
            }
            aPtr = aPtr->link;
        }
        Term* current = result.header->link;
        Term* prev = result.header;
        while (current != result.header) {
            if (current->coef == 0) {
                prev->link = current->link;
                result.deallocateTerm(current);
                current = prev->link;
            } else {
                prev = current;
                current = current->link;
            }
        }
        return result;
    }
    float Evaluate(float x) const {
        float result = 0;
        Term* current = header->link;
        while (current != header) {
            result += current->coef * pow(x, current->exp);
            current = current->link;
        }
        return result;
    }
};
int main() {
    Polynomial p1, p2;
    std::cin >> p1;
    std::cout << "p1 = " << p1 << std::endl;
    std::cin >> p2;
    std::cout << "p2 = " << p2 << std::endl;
    std::cout << "p1 + p2 = " << p1 + p2 << std::endl;
    std::cout << "p1 - p2 = " << p1 - p2 << std::endl;
    std::cout << "p1 * p2 = " << p1 * p2 << std::endl;
    std::cout << "p1(2.0) = " << p1.Evaluate(2.0) << std::endl;
    return 0;
}
```

## 效能分析

1. 時間複雜度： $O(n)$
2. 空間複雜度： $O(n)$

## 測試與驗證

### 測試案例
| 測試案例 | 輸入參數(n c1 e1 c2 e2) | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | 1 2 0 1 1 1   |  p1+p2=x+2           |     p1+p2=x+2               |
|         |               |  p1-p2=-x+2           |        p1-p2=-x+2              |             
|         |               |  p1*p2=2x           |    p1*p2=2x                  |    
|         |               |  p1(2.0)=2           |   p1(2.0)=2                 |    

### 結論


## 心得討論
- 設計考量: 循環鏈表與可用空間列表實現高效記憶體管理，確保節點重複利用。
- 挑戰: 乘法運算中合併相同指數項的實現較為簡化，實際應用中可加入排序以優化。
- 改進空間: 可增加指數排序功能，確保運算結果按降序排列，提升可讀性與一致性。
