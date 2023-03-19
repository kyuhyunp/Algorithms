#include <bits/stdc++.h> 
using namespace std;

int calcLunchTime(vector<pair<int, int>>& lunchTimes) {
    sort(lunchTimes.begin(), lunchTimes.end());

    int time = 0;
    int prepTimeSum = 0;
    for (auto it = lunchTimes.begin(); it < lunchTimes.end(); ++it) {
        prepTimeSum += it -> second;
        time = max(prepTimeSum + -(it -> first), time);
    }
    return time;
}

int main() {
    int numTests = 0;
    cin >> numTests;
    for (int test = 0; test < numTests; ++test) {
        int numLunch;
        cin >> numLunch;

        vector<int> prepTime(numLunch);
        for (int lunch = 0; lunch < numLunch; ++lunch) {
            cin >> prepTime[lunch];
        }

        vector<pair<int, int>> lunchTimes(numLunch);
        for (int lunch = 0; lunch < numLunch; ++lunch) {
            int eatTime;
            cin >> eatTime;
            lunchTimes[lunch] = make_pair(-eatTime, prepTime[lunch]);
        }

        cout << calcLunchTime(lunchTimes) << "\n";
    }

}