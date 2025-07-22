#include <iostream>
using namespace std;

int ackermann(int m, int n) {
    struct Call { int m, n; };
    Call stack[100000]; 
    int top = -1;
    stack[++top] = {m, n};
    
    while (top >= 0) {
        Call current = stack[top--];
        m = current.m;
        n = current.n;
        
        if (m == 0) {
            if (top == -1) {
                return n + 1;
            }
            stack[top].n = n + 1;
        } else if (n == 0) {
            stack[++top] = {m - 1, 1};
        } else {
            stack[++top] = {m - 1, -1}; 
            stack[++top] = {m, n - 1};
        }
    }
    return n; 
}
int main() {
    int m, n;
    cin >> m >> n;
    int result = ackermann(m, n);
    cout << result << '\n';
    return 0;
}
