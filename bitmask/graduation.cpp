#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
int numClasses, required, numSemesters, maxClasses;
vector<int> preReq;
vector<int> classes;
int cache[1 << 12][12];

int getBitMask() {
    int ret = 0;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        ret |= (1 << x);
    }
    return ret;
}

void findClassCombination(int maxSet, int lastRemoved, vector<int> &ret) {
    if (__builtin_popcount(maxSet) <= maxClasses) {
        ret.push_back(maxSet);
    }
    for (int cls = lastRemoved + 1; cls < numClasses; ++cls) {
        if ((maxSet & (1 << cls)) == 0) {
            continue;
        }
        findClassCombination(maxSet & (~(1 << cls)), cls, ret);
    }
}

vector<int> getClasses(int taken, int semester) {
    if (semester >= numSemesters) {
        return vector<int>();
    }

    int maxSet = 0;
    int cand = classes[semester] & (~taken);
    for (int cls = 0; cls < numClasses; ++cls) {
        if ((cand & (1 << cls)) == 0) {
            continue;
        }
        if ((taken & preReq[cls]) == preReq[cls]) {
            maxSet |= (1 << cls);
        }
    }

    vector<int> ret;
    findClassCombination(maxSet, -1, ret);
    return ret;
}

int getMinSemester(int taken, int lastSemester) {
    if (__builtin_popcount(taken) >= required) {
        return 0;
    }
    if (lastSemester >= numSemesters) {
        return INF;
    }

    int &ret = cache[taken][lastSemester + 1];
    if (ret != -1) {
        return ret;
    }

    ret = getMinSemester(taken, lastSemester + 1);
    vector<int> availableClasses = getClasses(taken, lastSemester + 1);
    for (int classes : availableClasses) {
        ret = min(ret, getMinSemester(classes | taken, lastSemester + 1) + 1);
    }
    return ret;
}

int main() {
    int numTests = 0;
    cin >> numTests;
    for (int test = 0; test < numTests; ++test) {
        memset(cache, -1, sizeof(cache));

        cin >> numClasses >> required >> numSemesters >> maxClasses;
        
        preReq.resize(numClasses);
        for (int cls = 0; cls < numClasses; ++cls) {
            preReq[cls] = getBitMask();
        }

        classes.resize(numSemesters);
        for(int semester = 0; semester < numSemesters; ++semester) {
            classes[semester] = getBitMask();
        }

        int ans = getMinSemester(0, -1);
        if (ans == INF) {
            cout << "IMPOSSIBLE\n";
        } else {
            cout << ans << "\n";
        }
    }
}