/*
    ============================================
    Programming 2 Project - Part 2
    Fayoum University - Faculty of FCAI
    Connect 4 Game on 7x7 Board
    ============================================
*/

#include <iostream>
using namespace std;

// ─── Constants ──────────────────────────────
const int ROWS = 7;
const int COLS = 7;

// ─── Global Variables ───────────────────────
char board[ROWS][COLS];

// ─── Function Declarations ──────────────────
void initBoard();
void displayBoard();
int  dropPiece(int col, char symbol);
bool checkWin(char symbol);
bool checkDraw();
void playGame();

// ============================================
// Initialize board with empty dots
// ============================================
void initBoard() {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            board[i][j] = '.';
}

// ============================================
// Display board - bottom row = row 6 visually
// ============================================
void displayBoard() {
    cout << "\n  Connect 4 - 7x7 Board\n";
    cout << "  Col:  1   2   3   4   5   6   7\n";
    cout << "       +---+---+---+---+---+---+---+\n";

    for (int i = 0; i < ROWS; i++) {
        cout << "       |";
        for (int j = 0; j < COLS; j++) {
            cout << " " << board[i][j] << " |";
        }
        cout << "\n       +---+---+---+---+---+---+---+\n";
    }
    cout << "\n";
}

// ============================================
// Drop piece into column (gravity simulation)
// Returns the row where it landed, or -1 if full
// ============================================
int dropPiece(int col, char symbol) {
    col--; // convert 1-based to 0-based

    if (col < 0 || col >= COLS) {
        cout << "  [!] Invalid column! Choose between 1 and 7.\n";
        return -1;
    }

    // Start from the bottom row and go up
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][col] == '.') {
            board[i][col] = symbol;
            return i; // return the row it landed on
        }
    }

    cout << "  [!] Column " << col + 1 << " is full! Choose another.\n";
    return -1; // column is full
}

// ============================================
// Check all 4-in-a-row directions for 'symbol'
// Directions: horizontal, vertical, diagonal
// ============================================
bool checkWin(char symbol) {
    // ── Horizontal Check ──
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j <= COLS - 4; j++) {
            if (board[i][j]   == symbol && board[i][j+1] == symbol &&
                board[i][j+2] == symbol && board[i][j+3] == symbol)
                return true;
        }
    }

    // ── Vertical Check ──
    for (int i = 0; i <= ROWS - 4; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j]   == symbol && board[i+1][j] == symbol &&
                board[i+2][j] == symbol && board[i+3][j] == symbol)
                return true;
        }
    }

    // ── Diagonal: top-left to bottom-right ──
    for (int i = 0; i <= ROWS - 4; i++) {
        for (int j = 0; j <= COLS - 4; j++) {
            if (board[i][j]     == symbol && board[i+1][j+1] == symbol &&
                board[i+2][j+2] == symbol && board[i+3][j+3] == symbol)
                return true;
        }
    }

    // ── Diagonal: top-right to bottom-left ──
    for (int i = 0; i <= ROWS - 4; i++) {
        for (int j = 3; j < COLS; j++) {
            if (board[i][j]     == symbol && board[i+1][j-1] == symbol &&
                board[i+2][j-2] == symbol && board[i+3][j-3] == symbol)
                return true;
        }
    }

    return false;
}

// ============================================
// Check if board is completely full (draw)
// ============================================
bool checkDraw() {
    for (int j = 0; j < COLS; j++)
        if (board[0][j] == '.')  // top row still has space
            return false;
    return true;
}

// ============================================
// Main game loop
// ============================================
void playGame() {
    initBoard();

    char currentSymbol = 'X';
    int  currentPlayer = 1;

    cout << "\n========================================\n";
    cout << "     Welcome to Connect 4 (7x7)!\n";
    cout << "  Player 1 = X  |  Player 2 = O\n";
    cout << "  Drop your piece by choosing a column\n";
    cout << "  First to connect 4 in a row wins!\n";
    cout << "========================================\n";

    while (true) {
        displayBoard();

        int col;
        cout << "  Player " << currentPlayer
             << " (" << currentSymbol << ") >> Choose column (1-7): ";
        cin >> col;

        // Drop piece; if invalid, try again
        int landedRow = dropPiece(col, currentSymbol);
        if (landedRow == -1)
            continue;

        // Check win
        if (checkWin(currentSymbol)) {
            displayBoard();
            cout << "  *** Player " << currentPlayer
                 << " (" << currentSymbol << ") WINS! Congratulations! ***\n\n";
            return;
        }

        // Check draw
        if (checkDraw()) {
            displayBoard();
            cout << "  *** It's a DRAW! The board is full! ***\n\n";
            return;
        }

        // Switch turn
        if (currentSymbol == 'X') { currentSymbol = 'O'; currentPlayer = 2; }
        else                       { currentSymbol = 'X'; currentPlayer = 1; }
    }
}

// ============================================
// Entry Point
// ============================================
int main() {
    char playAgain;

    do {
        playGame();

        cout << "  Play again? (y/n): ";
        cin >> playAgain;
        cout << "\n";

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "  Thanks for playing Connect 4! Goodbye.\n\n";
    return 0;
}
