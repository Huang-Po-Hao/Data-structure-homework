#include <iostream>
using namespace std;
int ackermann(int m, int n) {
    if (m==0) return n+1;
    else if (n==0) return ackermann(m-1,1);
    else return ackermann(m-1, ackermann(m,n-1));
}
int main() {
    int result=ackermann(2,2);
    cout<<result<<'\n'; 
    return 0;
}

