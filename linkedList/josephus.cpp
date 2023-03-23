#include <bits/stdc++.h>

using namespace std;

int numSoldiers;
int numSkips;

list<int> solve() {
    list<int> soldiers;
    for (int soldier = 1; soldier <= numSoldiers; ++soldier) {
        soldiers.push_back(soldier);
    }

    auto curr = soldiers.begin();
    while (soldiers.size() > 2) {
        curr = soldiers.erase(curr);
        if (curr == soldiers.end()) {
            curr = soldiers.begin();
        }

        for (int skip = 0; skip < numSkips - 1; ++skip) {
            ++curr;
            if (curr == soldiers.end()) {
                curr = soldiers.begin();
            }
        }

    }

    return soldiers;
}

int main() {
    int numTests = 0;
    cin >> numTests;
    for (int test = 0; test < numTests; ++test) {
        cin >> numSoldiers >> numSkips;
        list<int> ans = solve();
        int first = ans.front();
        int second = ans.back();

        if (second < first) {
            swap(first, second);
        }
        
        cout << first << " " << second << "\n";
    }
}