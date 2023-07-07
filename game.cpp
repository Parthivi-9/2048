#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int BOARD_SIZE = 4;
const int WINNING_TILE = 2048;

class Game2048 {
public:
    vector<vector<int>> board;
    int score;

    Game2048() : board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0)), score(0) {
        // Initialize the board with two random tiles
        addRandomTile();
        addRandomTile();
    }

    void printBoard() {
        cout << "Score: " << score << endl;
        for (int r = 0; r < BOARD_SIZE; ++r) {
            for (int c = 0; c < BOARD_SIZE; ++c) {
                cout << board[r][c] << "\t";
            }
            cout << endl;
        }
    }

    void addRandomTile() {
        // Find all empty tiles
        vector<pair<int, int>> emptyTiles;
        for (int r = 0; r < BOARD_SIZE; ++r) {
            for (int c = 0; c < BOARD_SIZE; ++c) {
                if (board[r][c] == 0) {
                    emptyTiles.push_back(make_pair(r, c));
                }
            }
        }

        // Randomly choose an empty tile
        srand(time(0));
        int numEmptyTiles = emptyTiles.size();
        if (numEmptyTiles > 0) {
            int index = rand() % numEmptyTiles;
            int value = (rand() % 2 + 1) * 2; // New tile can be either 2 or 4
            int row = emptyTiles[index].first;
            int col = emptyTiles[index].second;
            board[row][col] = value;
        }
    }

    bool isGameOver() {
        // Check if there are no empty tiles
        for (int r = 0; r < BOARD_SIZE; ++r) {
            for (int c = 0; c < BOARD_SIZE; ++c) {
                if (board[r][c] == 0) {
                    return false;
                }
            }
        }

        // Check if there are no adjacent matching tiles
        for (int r = 0; r < BOARD_SIZE; ++r) {
            for (int c = 0; c < BOARD_SIZE; ++c) {
                int currTile = board[r][c];
                if ((r < BOARD_SIZE - 1 && board[r + 1][c] == currTile) ||
                    (c < BOARD_SIZE - 1 && board[r][c + 1] == currTile)) {
                    return false;
                }
            }
        }

        return true;
    }

    void processMove(int move) {
        vector<vector<int>> prevBoard = board;

        if (move == 0) {
            // Move left
            for (int r = 0; r < BOARD_SIZE; ++r) {
                int index = 0;
                for (int c = 0; c < BOARD_SIZE; ++c) {
                    if (board[r][c] != 0) {
                        if (index > 0 && board[r][index - 1] == board[r][c]) {
                            // Merge tiles
                            board[r][index - 1] *= 2;
                            score += board[r][index - 1];
                        } else {
                            // Move tile
                            board[r][index] = board[r][c];
                            index++;
                        }
                    }
                }
                // Clear remaining tiles
                for (; index < BOARD_SIZE; ++index) {
                    board[r][index] = 0;
                }
            }
        } else if (move == 1) {
            // Move up
            for (int c = 0; c < BOARD_SIZE; ++c) {
                int index = 0;
                for (int r = 0; r < BOARD_SIZE; ++r) {
                    if (board[r][c] != 0) {
                        if (index > 0 && board[index - 1][c] == board[r][c]) {
                            // Merge tiles
                            board[index - 1][c] *= 2;
                            score += board[index - 1][c];
                        } else {
                            // Move tile
                            board[index][c] = board[r][c];
                            index++;
                        }
                    }
                }
                // Clear remaining tiles
                for (; index < BOARD_SIZE; ++index) {
                    board[index][c] = 0;
                }
            }
        } else if (move == 2) {
            // Move right
            for (int r = 0; r < BOARD_SIZE; ++r) {
                int index = BOARD_SIZE - 1;
                for (int c = BOARD_SIZE - 1; c >= 0; --c) {
                    if (board[r][c] != 0) {
                        if (index < BOARD_SIZE - 1 && board[r][index + 1] == board[r][c]) {
                            // Merge tiles
                            board[r][index + 1] *= 2;
                            score += board[r][index + 1];
                        } else {
                            // Move tile
                            board[r][index] = board[r][c];
                            index--;
                        }
                    }
                }
                // Clear remaining tiles
                for (; index >= 0; --index) {
                    board[r][index] = 0;
                }
            }
        } else if (move == 3) {
            // Move down
            for (int c = 0; c < BOARD_SIZE; ++c) {
                int index = BOARD_SIZE - 1;
                for (int r = BOARD_SIZE - 1; r >= 0; --r) {
                    if (board[r][c] != 0) {
                        if (index < BOARD_SIZE - 1 && board[index + 1][c] == board[r][c]) {
                            // Merge tiles
                            board[index + 1][c] *= 2;
                            score += board[index + 1][c];
                        } else {
                            // Move tile
                            board[index][c] = board[r][c];
                            index--;
                        }
                    }
                }
                // Clear remaining tiles
                for (; index >= 0; --index) {
                    board[index][c] = 0;
                }
            }
        }

        if (board != prevBoard) {
            // If the board has changed, add a new random tile
            addRandomTile();
        }
    }
};

int main() {
    Game2048 game;
    while (true) {
        game.printBoard();
        if (game.isGameOver()) {
            cout << "Game Over! Score: " << game.score << endl;
            break;
        }

        cout << "Enter move (0: Left, 1: Up, 2: Right, 3: Down): ";
        int move;
        cin >> move;

        if (move >= 0 && move <= 3) {
            game.processMove(move);
        } else {
            cout << "Invalid move! Please try again." << endl;
        }
        }

    return 0;
}
