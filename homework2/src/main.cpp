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
        }
        termArray[terms].coef = coef;
        termArray[terms].exp = exp;
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
    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;
        std::vector<Term> termsA(termArray, termArray + terms);
        std::vector<Term> termsB(other.termArray, other.termArray + other.terms);
        std::sort(termsA.begin(), termsA.end(), [](const Term& a, const Term& b) {
            return a.exp > b.exp;
        });
        std::sort(termsB.begin(), termsB.end(), [](const Term& a, const Term& b) {
            return a.exp > b.exp;
        });
        size_t i = 0, j = 0;
        while (i < termsA.size() || j < termsB.size()) {
            if (i < termsA.size() && j < termsB.size() && termsA[i].exp == termsB[j].exp) {
                float sumCoef = termsA[i].coef + termsB[j].coef;
                if (sumCoef != 0) {
                    result.newTerm(sumCoef, termsA[i].exp);
                }
                i++;
                j++;
            } else if (j >= termsB.size() || (i < termsA.size() && termsA[i].exp > termsB[j].exp)) {
                result.newTerm(termsA[i].coef, termsA[i].exp);
                i++;
            } else {
                result.newTerm(termsB[j].coef, termsB[j].exp);
                j++;
            }
        }
        return result;
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
    std::string line;
    std::getline(is, line);
    std::istringstream iss(line);
    float coef;
    int exp;
    while (iss >> coef >> exp) {
        poly.newTerm(coef, exp);
    }
    return is;
}
std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
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
    Polynomial polyA, polyB, polyC;
    std::cin >> polyA;
    std::cout << polyA << std::endl;
    return 0;
}
