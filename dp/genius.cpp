#include <bits/stdc++.h>
using namespace std;

const int MAX_DURATION = 4;

double probNext[51][51];
vector<int> durations;
vector<int> favorites;

int getDuration(int duration) {
    return (duration + MAX_DURATION + 1) % (MAX_DURATION + 1);
}

void printProbFavorites(int playTime, int numSongs) {
    vector<vector<double>> cache(MAX_DURATION + 1, vector<double>(numSongs, 0.0));

    // To improve: Use square matrix multiplication with divide and conquer algorithm
    cache[durations[0] % (MAX_DURATION + 1)][0] = 1.0;
    for (int duration = durations[0] + 1; duration < playTime + MAX_DURATION + 1; ++duration) {
        for (int song = 0; song < numSongs; ++song) {
            double &ans = cache[duration % (MAX_DURATION + 1)][song];
            ans = 0;
            for (int prevSong = 0; prevSong < numSongs; ++prevSong) {
                ans += cache[getDuration(duration - durations[song])][prevSong] 
                * probNext[prevSong][song];
            }
        }

    }

    for (int favorite : favorites) {
        double prob = 0;
        for (int duration = 1; duration <= durations[favorite]; ++duration) {
            prob += cache[(playTime + duration) % (MAX_DURATION + 1)][favorite];
        }
        cout << prob << " ";
    }
    cout << "\n";
}

int main() {
    std::cout << std::fixed;
    std::cout << std::setprecision(8);
    int numTests = 0;
    cin >> numTests;
    for (int test = 0; test < numTests; ++test) {
        int numSongs, playTime, numFavorites;
        cin >> numSongs >> playTime >> numFavorites;

        durations.resize(numSongs);
        for (int song = 0; song < numSongs; ++song) {
            cin >> durations[song];
        }

        for (int curr = 0; curr < numSongs; ++curr) {
            for (int next = 0; next < numSongs; ++next) {
                cin >> probNext[curr][next];
            }
        }

        favorites.resize(numFavorites);
        for (int song = 0; song < numFavorites; ++song) {
            cin >> favorites[song];
        }

        printProbFavorites(playTime, numSongs);
    }
}