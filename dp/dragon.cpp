#include <iostream>
#include <string>
#include <vector>
#include <utility> 
using namespace std;

long NUM_X_AND_Y[51];
long EXPANDED_LENGTH[51];

void preCalcNumXandY(int gen) {
    NUM_X_AND_Y[0] = 1;
    for (int i = 1; i <= gen; ++i) {
        NUM_X_AND_Y[i] = NUM_X_AND_Y[i-1] * 2;
    }
}


void preCalcExpandedLength(int gen) {
    preCalcNumXandY(gen);
    EXPANDED_LENGTH[0] = NUM_X_AND_Y[0];
    EXPANDED_LENGTH[1] = 4;
    for (int i = 2; i <= gen; ++i) {
        int numNonXY = EXPANDED_LENGTH[i-1] - NUM_X_AND_Y[i-1];
        EXPANDED_LENGTH[i] = NUM_X_AND_Y[i-1] * 4 + numNonXY;
    }
}

string expand(char ch) {
    if (ch == 'X') {
        return "X+YF";
    } 
    if (ch == 'Y') {
        return "FX-Y";
    } 
    return string(1, ch);
}

/**
* Pre-condition: 0 <= gen <= 50
* Post-condition: Calculate [begin, end) range for each expanded character
*/
vector<pair<long, long>> getExpandedBeginEnd(int gen, const string &dragonCurve) {
    vector<pair<long, long>> expandedBeginEnd(dragonCurve.length());
    for (int idx = 0; idx < dragonCurve.length(); ++idx) {
        long expandedLength = 1;
        if (dragonCurve[idx] == 'X' || dragonCurve[idx] == 'Y') {
            expandedLength = EXPANDED_LENGTH[gen];
        } 
        
        long begin = 0; // 0-indexed
        if (idx != 0) {
            begin = expandedBeginEnd[idx - 1].second;
        }
        expandedBeginEnd[idx] = make_pair(begin, begin + expandedLength);
    }
    return expandedBeginEnd;
}

string getDragonCurve(int gen, int start, int len, const string &seed) {
    string dragonCurve = seed;
    --start; // 0-indexed
    int nextStart = start;

    while (gen > 0) {
        vector<pair<long, long>> expandedBeginEnd = getExpandedBeginEnd(gen, dragonCurve);

        // seed[startIdx, endIdx)
        int startIdx = -1;
        int endIdx = -1;

        // Could use binary search to speed this up
        for (int idx = 0; idx < expandedBeginEnd.size(); ++idx) {
            long begin = expandedBeginEnd[idx].first;
            long end = expandedBeginEnd[idx].second;

            if (end <= start) {
                nextStart -= (end - begin);
            } 

            if (startIdx == -1 && end > start) {
                startIdx = idx;
            }

            if (endIdx == -1 && start + len <= end) {
                endIdx = idx + 1;
            }
        }
       
        dragonCurve = string(dragonCurve.begin() + startIdx, dragonCurve.begin() + endIdx);
        start = nextStart;
        --gen;

        string expanded = "";
        for (int idx = 0; idx < dragonCurve.length(); ++idx) {
            expanded += expand(dragonCurve[idx]);
        }
        dragonCurve = expanded;
    }

    return string(dragonCurve.begin() + start, dragonCurve.begin() + start + len);
}

/**
 * A slower method to check against getDragonCurve solution
*/
string getDragonCurveNaive(int gen, int start, int len, const string &seed) {
    string dragonCurve = seed;
    while (gen > 0) {
        string expanded = "";
        for (char ch : dragonCurve)  {
            expanded += expand(ch);
        }
        dragonCurve = expanded;
        --gen;
    }
    --start;
    return string(dragonCurve.begin() + start, dragonCurve.begin() + start + len);
}





int main() {
    preCalcExpandedLength(50);

    int numTests = 0;
    cin >> numTests;
    for (int test = 0; test < numTests; ++test) {
        int gen, start, len;
        cin >> gen >> start >> len;
        cout << getDragonCurve(gen, start, len, "FX") << "\n";
    }
}