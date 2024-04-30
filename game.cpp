#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

const int SIZE = 9;
const int SUBGRID_SIZE = 3;

// Function to print the Sudoku grid
void printGrid(vector<vector<int>>& grid) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << grid[i][j] << " ";
            if ((j + 1) % SUBGRID_SIZE == 0 && j < SIZE - 1)
                cout << "| ";
        }
        cout << endl;
        if ((i + 1) % SUBGRID_SIZE == 0 && i < SIZE - 1) {
            for (int k = 0; k < SIZE + SUBGRID_SIZE - 1; ++k)
                cout << "--";
            cout << endl;
        }
    }
}

// Function to check if the value can be placed at the given position
bool isValid(vector<vector<int>>& grid, int row, int col, int num) {
    // Check row and column
    for (int i = 0; i < SIZE; ++i) {
        if (grid[row][i] == num || grid[i][col] == num)
            return false;
    }

    // Check subgrid
    int startRow = row - row % SUBGRID_SIZE;
    int startCol = col - col % SUBGRID_SIZE;
    for (int i = startRow; i < startRow + SUBGRID_SIZE; ++i) {
        for (int j = startCol; j < startCol + SUBGRID_SIZE; ++j) {
            if (grid[i][j] == num)
                return false;
        }
    }

    return true;
}

// Function to solve Sudoku using backtracking
bool solveSudoku(vector<vector<int>>& grid) {
    int row, col;

    // Find an empty cell
    bool foundEmpty = false;
    for (row = 0; row < SIZE; ++row) {
        for (col = 0; col < SIZE; ++col) {
            if (grid[row][col] == 0) {
                foundEmpty = true;
                break;
            }
        }
        if (foundEmpty) break;
    }

    // If no empty cell found, puzzle is solved
    if (!foundEmpty) return true;

    // Try placing numbers from 1 to 9
    for (int num = 1; num <= SIZE; ++num) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num;

            // Recursively solve the remaining grid
            if (solveSudoku(grid)) return true;

            // Backtrack if the solution is not possible with this number
            grid[row][col] = 0;
        }
    }

    return false;
}

// Function to generate a Sudoku puzzle
void generateSudoku(vector<vector<int>>& grid) {
    // Seed random number generator
    srand(time(0));

    // Solve a complete Sudoku puzzle
    solveSudoku(grid);

    // Remove numbers to create a puzzle
    int numToRemove = SIZE * SIZE / 2; // Remove half of the numbers
    while (numToRemove > 0) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;
        if (grid[row][col] != 0) {
            grid[row][col] = 0;
            numToRemove--;
        }
    }
}

int main() {
    vector<vector<int>> grid(SIZE, vector<int>(SIZE, 0));

    // Generate Sudoku puzzle
    generateSudoku(grid);

    // Print Sudoku grid
    printGrid(grid);

    return 0;
}
