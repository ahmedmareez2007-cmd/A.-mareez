#include <iostream>
using namespace std;

// ─── Global Variables ───────────────────────
char board[4][4];      // The 4x4 game board
int movesCount;        // Tracks total moves made

// ─── Function Declarations ──────────────────
void initBoard();
void displayBoard();
bool makeMove(int row, int col, char symbol);
bool checkWin(char symbol);
bool checkDraw();
void playGame();

// ============================================
// Initialize board with empty spaces
// ============================================
void initBoard() {
    movesCount = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            board[i][j] = '.';
}

// ============================================
// Display the current board state
// ============================================
void displayBoard() {
    cout << "\n    Col: 1   2   3   4\n";
    cout << "         ---+---+---+---\n";
    for (int i = 0; i < 4; i++) {
        cout << "Row " << i + 1 << ":  ";
        for (int j = 0; j < 4; j++) {
            cout << " " << board[i][j];
            if (j < 3) cout << " |";
        }
        cout << "\n";
        if (i < 3)
            cout << "         ---+---+---+---\n";
    }
    cout << "\n";
}

// ============================================
// Make a move: returns false if cell is taken
// ============================================
bool makeMove(int row, int col, char symbol) {
    // Convert 1-based input to 0-based index
    row--; col--;

    if (row < 0 || row > 3 || col < 0 || col > 3) {
        cout << "  [!] Invalid position! Enter row/col between 1 and 4.\n";
        return false;
    }
    if (board[row][col] != '.') {
        cout << "  [!] Cell already taken! Choose another.\n";
        return false;
    }

    board[row][col] = symbol;
    movesCount++;
    return true;
}

// ============================================
// Check if a player with 'symbol' has won
// Checks: all rows, all cols, both diagonals
// ============================================
bool checkWin(char symbol) {
    // Check rows
    for (int i = 0; i < 4; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol &&
            board[i][2] == symbol && board[i][3] == symbol)
            return true;
    }

    // Check columns
    for (int j = 0; j < 4; j++) {
        if (board[0][j] == symbol && board[1][j] == symbol &&
            board[2][j] == symbol && board[3][j] == symbol)
            return true;
    }

    // Check main diagonal (top-left to bottom-right)
    if (board[0][0] == symbol && board[1][1] == symbol &&
        board[2][2] == symbol && board[3][3] == symbol)
        return true;

    // Check anti-diagonal (top-right to bottom-left)
    if (board[0][3] == symbol && board[1][2] == symbol &&
        board[2][1] == symbol && board[3][0] == symbol)
        return true;

    return false;
}

// ============================================
// Check if the board is completely full
// ============================================
bool checkDraw() {
    return movesCount == 16; // 4x4 = 16 cells
}

// ============================================
// Main game loop
// ============================================
void playGame() {
    initBoard();

    char currentSymbol = 'X';  // X always goes first
    int currentPlayer  = 1;

    cout << "\n========================================\n";
    cout << "       Welcome to 4x4 XO Game!\n";
    cout << "  Player 1 = X  |  Player 2 = O\n";
    cout << "  Enter row then column (1 to 4)\n";
    cout << "========================================\n";

    while (true) {
        displayBoard();

        int row, col;
        cout << "  Player " << currentPlayer
             << " (" << currentSymbol << ") >> Enter row: ";
        cin >> row;
        cout << "  Player " << currentPlayer
             << " (" << currentSymbol << ") >> Enter col: ";
        cin >> col;

        // Validate and place move
        if (!makeMove(row, col, currentSymbol))
            continue; // Invalid move, ask again

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
            cout << "  *** It's a DRAW! Well played both! ***\n\n";
            return;
        }

        // Switch player
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

    cout << "  Thanks for playing! Goodbye.\n\n";
    return 0;
}
