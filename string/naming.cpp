#include <bits/stdc++.h>
using namespace std;

string s;

/*
    pi[i] records length of the largest suffix of the prefix s[0..i]
*/
vector<int> pi;

void calcPartialMatch() {
    pi.resize(s.size());
    int n = s.size();
    pi[0] = 0;
    int suffixBegin = 1; // 1 because suffix should be shorter than s
    int match = 0;
    // finding the biggest suffix of prefix
    while (suffixBegin + match < n) {
        // matching suffix with prefix
        if (s[match] == s[suffixBegin + match]) {
            ++match;
            pi[suffixBegin + match - 1] = match;
        } else {
            if (match == 0) {
                ++suffixBegin;
                pi[suffixBegin + match - 1] = 0;
            } else {
                suffixBegin += match - pi[match - 1];
                match = pi[suffixBegin];
            }
        }
    }
}

int main() {
    string dad;
    string mom;
    cin >> dad;
    cin >> mom;

    s = dad + mom;
    
    calcPartialMatch();

    // keep finding the largest partial match of the largest prefix
    stack<int> answers;
    int answer = s.size();
    while (answer > 0) {
        answers.push(answer);
        answer = pi[answer - 1];
    }

    while (!answers.empty()) {
        cout << answers.top() << " ";
        answers.pop();
    }
    cout << "\n";
}