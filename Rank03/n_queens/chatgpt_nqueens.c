#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 4 // Change this value for different board sizes

// Function to print the chessboard
void printSolution(int board[N][N]) 
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%s ", board[i][j] ? "Q" : ".");
        }
        printf("\n");
    }
    printf("\n");
}

// Function to check if placing a queen at board[row][col] is safe
bool isSafe(int board[N][N], int row, int col) 
{
    int i, j;

    // Check the same column
    for (i = 0; i < row; i++) {
        if (board[i][col]) {
            return false;
        }
    }

    // Check the upper-left diagonal
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    // Check the upper-right diagonal
    for (i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j]) {
            return false;
        }
    }
    return true;
}

// Recursive function to solve the N-Queens problem
bool solveNQueensUtil(int board[N][N], int row) 
{
    // If all queens are placed, return true
    if (row >= N) {
        printSolution(board);
        return true; // Return false if you want all solutions
    }

    bool success = false;

    // Try placing a queen in all columns of the current row
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            // Place the queen
            board[row][col] = 1;

            // Recursively place the next queen
            success = solveNQueensUtil(board, row + 1) || success;

            // Backtrack: Remove the queen if it leads to a conflict
            board[row][col] = 0;
        }
    }
    return success;
}

// Function to solve the N-Queens problem
void solveNQueens() 
{
    int board[N][N] = {0}; // Initialize the board with all zeros

    if (!solveNQueensUtil(board, 0)) {
        printf("No solution exists for N = %d\n", N);
    }
}

int main() 
{
    solveNQueens();
    return 0;
}

