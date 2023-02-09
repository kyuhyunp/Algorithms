#include <bits/stdc++.h>
using namespace std;

const char AVAILABLE = '.';
const char UNAVAILABLE = '#';
const char UNSOLVED = -1;
const int BOARD_SIZE = 5;

char cache[(1 << 25)];

vector<int> moves;

int getCell(int y, int x) {
    return 1 << (5 * y + x);
}

void recordAllMoves() {
    // 25 choose 3 = 2300
    moves.reserve(2300);

    // Recording L shaped blocks
    for (int y = 0; y < BOARD_SIZE - 1; ++y) {
        for (int x = 0; x < BOARD_SIZE - 1; ++x) {
            int block = 0;
            for (int dy = 0; dy <= 1; ++dy) {
                for (int dx = 0; dx <= 1; ++dx) {
                    block |= getCell(y + dy, x + dx);
                }
            }

            for (int dy = 0; dy <= 1; ++dy) {
                for (int dx = 0; dx <= 1; ++dx) {
                    moves.push_back(block - getCell(y + dy, x + dx));
                }
            }
        }
    }

    // Recording size 2 blocks
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE - 1; ++j) {
            int horizontal = getCell(i, j) + getCell(i, j + 1);
            int vertical = getCell(j, i) + getCell(j + 1, i);
            moves.push_back(horizontal);
            moves.push_back(vertical);
        }
    }
}

char canWin(int visited) {
    char &ret = cache[visited];
    if (ret != UNSOLVED) {
        return ret;
    }

    for (int move : moves) {
        if (visited & move) {
            continue;
        }

        // If the opponent can't win in the next turn, I can win
        if (!canWin(visited | move)) {
            return ret = 1;
        }
    }

    return ret = 0;
}


int main() {
    recordAllMoves();

    int numGames = 0;
    cin >> numGames;
    for (int game = 0; game < numGames; ++game) {
        memset(cache, UNSOLVED, sizeof(cache));

        int visited = 0;
        for (int y = 0; y < BOARD_SIZE; ++y) {
            for (int x = 0; x < BOARD_SIZE; ++x) {
                char cellVal;
                cin >> cellVal;
                if (cellVal == UNAVAILABLE) {
                    visited |= getCell(y, x);
                }
            }
        }

        cout << (canWin(visited) ? "WINNING": "LOSING") << "\n";
    }
}

