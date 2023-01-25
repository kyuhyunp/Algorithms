#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;
const int MAX_PICKED = (1 << 15) + 1;
const int MAX_DIVISOR = 20;
const int MAX_MATCHING = 2;

int cache[MAX_PICKED][MAX_DIVISOR][MAX_MATCHING];
long eggPrice;
long candyCount;


int calcTenModulus(int digit) {
    int ret = 1;
    for (int i = 0; i < digit; ++i) {
        ret = (ret * 10) % candyCount;
    }
    return ret;
}

int countPossibleEggPrice(int picked, int divisor, int matching, 
                            const vector<int> &eggPriceDigits, const vector<int> &eggPriceDigitsSorted) {
    int pickedCount = __builtin_popcount(picked);
    if (pickedCount >= eggPriceDigits.size()) {
        return (divisor == 0 && !matching);
    }

    int &ret = cache[picked][divisor][matching];
    if (ret != -1) {
        return ret;
    }

    ret = 0;
    for (int digit = 0; digit < eggPriceDigitsSorted.size(); ++digit) {
        int cand = eggPriceDigitsSorted[digit];
        int currentDigit = eggPriceDigits[pickedCount];
        if ((picked & (1 << digit)) || (matching && cand > currentDigit)) {
            continue;
        }
        if (digit != 0 && cand == eggPriceDigitsSorted[digit - 1] && !(picked & (1 << (digit - 1)))) {
            continue;
        }

        int nextPicked = (picked | (1 << digit));
        int nextDivisor = (divisor + calcTenModulus(eggPriceDigits.size() - pickedCount - 1) * cand) % candyCount;
        if (matching && cand == currentDigit) {
            ret = (ret + countPossibleEggPrice(nextPicked, nextDivisor, 1, eggPriceDigits, eggPriceDigitsSorted)) % MOD;
        } else {
            ret = (ret + countPossibleEggPrice(nextPicked, nextDivisor, 0, eggPriceDigits, eggPriceDigitsSorted)) % MOD;
        }
    }

    return ret;
}

vector<int> getDigitsReversed(long num) {
    vector<int> digits;
    while (num != 0) {
        digits.push_back(num % 10);
        num /= 10;
    }
    reverse(digits.begin(), digits.end());
    return digits;
}

int main() {
    int numTests;
    cin >> numTests;
    for (int test = 0; test < numTests; ++test) {
        cin >> eggPrice >> candyCount;
        for (int picked = 0; picked < MAX_PICKED; ++picked) {
            for (int divisor = 0; divisor < MAX_DIVISOR; ++divisor) {
                for (int matching = 0; matching < MAX_MATCHING; ++matching) {
                    cache[picked][divisor][matching] = -1;
                }
            }
        }
        vector<int> eggPriceDigits = getDigitsReversed(eggPrice);
        vector<int> eggPriceDigitsSorted(eggPriceDigits.begin(), eggPriceDigits.end());
        sort(eggPriceDigitsSorted.begin(), eggPriceDigitsSorted.end());

        cout << countPossibleEggPrice(0, 0, 1, eggPriceDigits, eggPriceDigitsSorted) << "\n";
    }
}