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
        is >> n;
        if (n == 0) return is;
        Term* current = p.header;
        for (int i = 0; i < n; ++i) {
            int c, e;
            is >> c >> e;
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

    // (d) Assignment Operator
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
    std::cin >> p2;
    std::cout << "p1 + p2 = " << p1 + p2 << std::endl;
    std::cout << "p1 - p2 = " << p1 - p2 << std::endl;
    std::cout << "p1 * p2 = " << p1 * p2 << std::endl;
    std::cout << "p1(2.0) = " << p1.Evaluate(2.0) << std::endl;
    return 0;
} 
