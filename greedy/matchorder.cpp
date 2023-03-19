#include <bits/stdc++.h>

using namespace std;


int getMaxWins(const vector<int> &russians, const vector<int> &koreans) {
    multiset<int> ratings(koreans.begin(), koreans.end());
    
    int wins = 0;
    for (int russian : russians) {
        if (*ratings.rbegin() < russian) {
            ratings.erase(ratings.begin());
        } else {
            ratings.erase(ratings.lower_bound(russian));
            ++wins;
        }
    }
    return wins;
}

int main() {
    int numTests = 0;
    cin >> numTests;
    for (int test = 0; test < numTests; ++test) {
        int numPlayers;
        cin >> numPlayers;

        vector<int> russians(numPlayers);
        for (int rus = 0; rus < numPlayers; ++rus) {
            cin >> russians[rus];
        }

        vector<int> koreans(numPlayers);
        for (int kor = 0; kor < numPlayers; ++kor) {
            cin >> koreans[kor];
        }

        cout << getMaxWins(russians, koreans) << "\n";
    }
}