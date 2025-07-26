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
