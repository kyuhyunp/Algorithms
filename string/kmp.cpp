#include <bits/stdc++.h>
using namespace std;


/**
    partial match[i] is the length of the biggest prefix of N[0..i]
    that is also a suffix of N[0..i] excluding N[0..i]
*/
vector<int> partialMatch;

void calcPartialMatch(const string& N) {
    int n = N.size();
    partialMatch.resize(n);

    partialMatch[0] = 0;
    int begin = 1;
    int matched = 0;

    while (begin + matched < n) {
        if (N[begin + matched] == N[matched]) {
            ++matched;
            partialMatch[begin + matched - 1] = matched;
        } else {
            if (matched == 0) {
                ++begin;
                partialMatch[begin + matched - 1] = 0;
            } else {
                begin += matched - partialMatch[matched - 1];
                matched = partialMatch[matched - 1];
            }
        }
    }

    


}

vector<int> kmpSearch(const string& H, const string& N) {
    int n = H.size();
    int m = N.size();

    int begin = 0;
    int matched = 0;
    vector<int> ret;

    while (begin + m <= n) {
        if (matched < m && H[begin + matched] == N[matched]) {
            ++matched;
            if (matched == m) {
                ret.push_back(begin);
            }
        } else {
            if (matched == 0) {
                ++begin;
            } else {
                begin += matched - partialMatch[matched - 1];
                matched = partialMatch[matched - 1];
            }
        }
    }

    return ret;
}

int main() {
    string H = "aabaabac";
    string N = "aabaa";
    calcPartialMatch(N);
    for (int i = 0; i < N.size(); ++i) { 
        cout << partialMatch[i] << " ";
    }
    cout << "\n";

    vector<int> res = kmpSearch(H, N);
    for (int x : res) {
        cout << x << " ";
    }
    cout << "\n";
}