#include <bits/stdc++.h>
using namespace std;

const int MAX_BUDGET = 21474836;
int prices[21];
int preferences[21];
int cache[MAX_BUDGET + 1]; // Records the maximum preference
 
int getMaxPreference(int menuCount, int budget) {
    budget /= 100;

    for (int menu = 0; menu < menuCount; ++menu) {
        for (int price = 0; price <= budget; ++price) {
            if (menu == 0) {
                if (price < prices[menu]) {
                    cache[price] = 0;
                } else {
                    cache[price] = cache[price - prices[menu]] + preferences[menu];
                }
            } else {
                if (price >= prices[menu]) {
                    cache[price] = max(cache[price], cache[price - prices[menu]] + preferences[menu]);
                } 
            } 
        }
    }
    return cache[budget];
}
 

int main() {
    int numTests = 0;
    cin >> numTests;
    for (int test = 0; test < numTests; ++test) {
        int menuCount, budget;
        cin >> menuCount >> budget;

        for (int menu = 0; menu < menuCount; ++menu) {
            cin >> prices[menu] >> preferences[menu];
            prices[menu] /= 100;
        }

        cout << getMaxPreference(menuCount, budget) << '\n';
    }
}