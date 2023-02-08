#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int MAX_PICKED = (1 << 15);
const int MAX_PARTS = 17;
const int INF = 987654321;
int cache[MAX_PICKED][MAX_PARTS];


bool isSubstring(const string &cand, const vector<string> &includedParts) {
    for (string included : includedParts) {
        if (cand.size() > included.size()) {
            continue;
        }
        if (included.find(cand) != string::npos) {
            return true;
        }
    }
    return false;
}


int getOverlappedLength(const string &pred, const string &succ) {
    int sz1 = pred.size();
    int sz2 = succ.size();
    int diff = sz1-sz2;
    int start = max(diff, 0);
    for (int preceding = start; preceding < sz1; ++preceding) {
        for (int succeeding = 0; succeeding < (sz1 - preceding); ++succeeding) {
            if (pred[preceding + succeeding] != succ[succeeding]) {
                break;
            }
            if (succeeding == (sz1 - preceding - 1)) {
                return sz1 - preceding;
            }
        }
    }
    return 0;
}

vector<vector<int>> getNonOverlappedLengths(const vector<string> &parts) {
    int len = parts.size();
    vector<vector<int>> nonOverlappedLengths(len, vector<int>(len));
    for (int preceding = 0; preceding < len; ++preceding) {
        for (int succeeding = 0; succeeding < len; ++succeeding) {
            if (preceding == succeeding) {
                nonOverlappedLengths[preceding][succeeding] = parts[succeeding].size();
            } else {
                nonOverlappedLengths[preceding][succeeding] = parts[succeeding].size() - 
                getOverlappedLength(parts[preceding], parts[succeeding]);
            }
        }
    }

    return nonOverlappedLengths;
}


int getMinRestoredLength(int picked, int lastPicked, const vector<vector<int>> &nonOverlappedLengths) {
    int &ret = cache[picked][lastPicked + 1];
    if (ret != -1) {
        return ret;
    }

    int pickedCount = __builtin_popcount(picked);
    if (pickedCount == nonOverlappedLengths.size()) {
        return ret = 0;
    }

    ret = INF;
    for (int next = 0; next < nonOverlappedLengths.size(); ++next) {
        if ((picked & (1 << next))) {
            continue;
        }

        int nonOverlappedLength = nonOverlappedLengths[next][next];
        if (lastPicked != -1) {
            nonOverlappedLength = nonOverlappedLengths[lastPicked][next];
        }

        ret = min(ret, nonOverlappedLength + getMinRestoredLength((picked | (1 << next)), next, nonOverlappedLengths));
    }

    return ret;
}

void restore(int picked, int lastPicked, string &restored, const vector<string> &parts, const vector<vector<int>> &nonOverlappedLengths) {
    int pickedCount = __builtin_popcount(picked);
    if (pickedCount == parts.size()) {
        return;
    }

    int minimum = INF;
    int choice = -1;
    for (int i = 0; i < parts.size(); ++i) {
        if (picked & (1 << i)) {
            continue;
        }
        int cand = parts[i].size() + cache[(picked|(1 << i))][i + 1];
        if (minimum > cand) {
            minimum = cand;
            choice = i;
        }
    }
    
    string part = parts[choice];
    if (lastPicked == -1) {
        restored += part;
    } else {
        int nonOverlappedLength = nonOverlappedLengths[lastPicked][choice];
        restored += part.substr(part.size() - nonOverlappedLength);
    }

    restore((picked|(1 << choice)), choice, restored, parts, nonOverlappedLengths);
}

int main() {
    int numTests = 0;
    cin >> numTests;
    for (int test = 0; test < numTests; ++test) {
        int stringCount;
        cin >> stringCount;
        vector<string> parts(stringCount);
        for (int part = 0; part < stringCount; ++part) {
            cin >> parts[part];
        }

        vector<pair<int, string>> partsByLengthDec;
        partsByLengthDec.reserve(stringCount);
        for (string part: parts) {
            partsByLengthDec.push_back(make_pair(100 - part.size(), part));
        }
        sort(partsByLengthDec.begin(), partsByLengthDec.end());

        vector<string> exclusiveParts;
        exclusiveParts.reserve(stringCount);
        for (auto cand : partsByLengthDec) {
            if (!isSubstring(cand.second, exclusiveParts)) {
                exclusiveParts.push_back(cand.second);
            }
        }
        
        vector<vector<int>> nonOverlappedLengths = getNonOverlappedLengths(exclusiveParts);
        for (int picked = 0; picked < MAX_PICKED; ++picked) {
            for (int part = 0; part < MAX_PARTS; ++part) {
                cache[picked][part] = -1;
            }
        }
        getMinRestoredLength(0, -1, nonOverlappedLengths);

        string restored = "";
        restore(0, -1, restored, exclusiveParts, nonOverlappedLengths);
        cout << restored << "\n";
    }
}