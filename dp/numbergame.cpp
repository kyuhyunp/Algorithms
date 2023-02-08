#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 51;
const int INITIAL = -50001;
vector<int> numbers;
int cache[MAX_SIZE][MAX_SIZE]; // init to 50001 (INITIAL)

/*
    Inclusive range left, right in numbers
*/
int getScoreDiff(int left, int right) {
    // Check if there are no more numbers left
    if (left - 1 == right) {
        return 0;
    } 

    // 1) Take left or right and erase
    // 2) Erase two from left or right
    int &ret = cache[left][right];
    if (ret != INITIAL) {
        return ret;
    }

    int leftTake = numbers[left] - getScoreDiff(left + 1, right);
    int rightTake = numbers[right] - getScoreDiff(left, right - 1);
    ret = max(leftTake, rightTake);

    if (left < right) {
        int leftSkip = 0 - getScoreDiff(left + 2, right);
        int rightSkip = 0 - getScoreDiff(left, right - 2);
        ret = max(ret, max(leftSkip, rightSkip));
    }
    return ret;
}

int main() {
    int numTests = 0;
    cin >> numTests;
    for (int test = 0; test < numTests; ++test) {
        int boardSize;
        cin >> boardSize;
        numbers.reserve(boardSize);

        for (int left = 0; left < MAX_SIZE; ++left) {
            for (int right = 0; right < MAX_SIZE; ++right) {
                cache[left][right] = INITIAL;
            }
        }

        for (int idx = 0; idx < boardSize; ++idx) {
            cin >> numbers[idx];
        }

        cout << getScoreDiff(0, boardSize - 1) << "\n";
        numbers.clear();
    }
}






