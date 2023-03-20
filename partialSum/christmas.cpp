#include <bits/stdc++.h>

using namespace std;

const int MOD = 20091101;
int numBoxes, numChildren;
vector<int> numDolls;

void solve(const vector<int> &partialSum, pair<int, int>& ans) {
    unordered_map<int, vector<int>> numDollsToIndices;

    vector<pair<int, int>> intervalEndToStart;
    for (int idx = 0; idx < partialSum.size(); ++idx) {
        auto it = numDollsToIndices.find(partialSum[idx]);
        if (it != numDollsToIndices.end()) {
            ans.first += (it -> second).size();
            ans.first %= MOD;
            intervalEndToStart.push_back(make_pair(idx, (it -> second).back()));
        } 
        numDollsToIndices[partialSum[idx]].push_back(idx);
    }

    sort(intervalEndToStart.begin(), intervalEndToStart.end());
    int end = -1;
    for (auto it : intervalEndToStart) {
        if (end <= it.second) {
            end = it.first;
            ++ans.second;
            ans.second %= MOD;
        }
    }
}

vector<int> calcPartialSum() {
    vector<int> partialSum(numBoxes + 1);

    partialSum[0] = 0;
    for (int box = 0; box < numBoxes; ++box) {
        partialSum[box + 1] = partialSum[box] + numDolls[box];
        partialSum[box + 1] %= numChildren;
    }

    return partialSum;
}

int main() {
    ios_base::sync_with_stdio(false);

    int numTests = 0;
    cin >> numTests;

    for (int test = 0; test < numTests; ++test) {
        cin >> numBoxes >> numChildren;

        numDolls.resize(numBoxes);
        for (int box = 0; box < numBoxes; ++box) {
            cin >> numDolls[box];
        }

        vector<int> partialSum = calcPartialSum();
        pair<int, int> ans;
        solve(partialSum, ans);
        cout << ans.first << " " << ans.second << "\n";
    }

}