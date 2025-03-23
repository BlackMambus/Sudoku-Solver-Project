#include <iostream>
#include <vector>

using namespace std;

// Size of the Sudoku grid
#define N 9

// Function to print the Sudoku grid
void printBoard(const vector<vector<int>>& board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if a number is valid in the current position
bool isSafe(const vector<vector<int>>& board, int row, int col, int num) {
    // Check the row
    for (int x = 0; x < N; x++) {
        if (board[row][x] == num) {
            return false;
        }
    }

    // Check the column
    for (int x = 0; x < N; x++) {
        if (board[x][col] == num) {
            return false;
        }
    }

    // Check the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(vector<vector<int>>& board) {
    int row, col;

    // Check if there is any empty cell (denoted by 0)
    bool emptyCellFound = false;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (board[row][col] == 0) {
                emptyCellFound = true;
                break;
            }
        }
        if (emptyCellFound) {
            break;
        }
    }

    // If no empty cell is found, the Sudoku is solved
    if (!emptyCellFound) {
        return true;
    }

    // Try numbers 1-9 for the empty cell
    for (int num = 1; num <= N; num++) {
        // If it's safe to place the number
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;

            // Recursively attempt to solve with this number
            if (solveSudoku(board)) {
                return true;
            }

            // If placing num doesn't lead to a solution, backtrack
            board[row][col] = 0;
        }
    }

    // If no number can be placed, return false (backtrack)
    return false;
}

int main() {
    // Example Sudoku puzzle (0 represents empty cells)
    vector<vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Initial Sudoku Puzzle:" << endl;
    printBoard(board);

    if (solveSudoku(board)) {
        cout << "\nSolved Sudoku Puzzle:" << endl;
        printBoard(board);
    } else {
        cout << "\nNo solution exists!" << endl;
    }

    return 0;
}


