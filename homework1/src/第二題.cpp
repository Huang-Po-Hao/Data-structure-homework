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
