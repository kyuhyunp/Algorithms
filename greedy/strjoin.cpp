#include <bits/stdc++.h>

using namespace std;

// O(n log n)
int minJoinCost(const vector<int> &lengths) {
    // O(n)
    priority_queue<int, vector<int>, greater<int>> orderedLengths(lengths.begin(), lengths.end());

    int cost = 0;
    // O(n)
    while (orderedLengths.size() > 1) {
        // O(1)
        int first = orderedLengths.top();
        orderedLengths.pop();
        int second = orderedLengths.top();
        orderedLengths.pop();

        // O(log n)
        cost += (first + second);
        orderedLengths.push(first + second);
    }

    return cost;
}

int main() {
    int numTests = 0;
    cin >> numTests;

    for (int test = 0; test < numTests; ++test) {
        int numStr = 0;
        cin >> numStr;
        vector<int> lengths(numStr);

        for (int str = 0; str < numStr; ++str) {
            cin >> lengths[str];
        }

        cout << minJoinCost(lengths) << "\n";
    }
}