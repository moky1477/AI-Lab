#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3

// Function to print the Tic-Tac-Toe board
void printBoard(char board[SIZE][SIZE]) {
    printf("-------------\n");
    for (int i = 0; i < SIZE; i++) {
        printf("| ");
        for (int j = 0; j < SIZE; j++) {
            printf("%c | ", board[i][j]);
        }
        printf("\n-------------\n");
    }
}

// Function to check if the game is over
int isGameOver(char board[SIZE][SIZE], char player) {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return 1; // Player wins
        }
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return 1; // Player wins
    }

    // Check for a draw
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ')
                return 0; // The game is not over yet
        }
    }

    return -1; // It's a draw
}

// Function to check if a move is valid
int isValidMove(char board[SIZE][SIZE], int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE)
        return 0; // Out of bounds
    if (board[row][col] != ' ')
        return 0; // Cell is already occupied
    return 1; // Valid move
}

// Function for the computer's move (strategic)
void computerMove(char board[SIZE][SIZE], char player) {
    // Try to win
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = player;
                if (isGameOver(board, player)) {
                    return; // Winning move found
                }
                board[i][j] = ' '; // Undo the move
            }
        }
    }

    // Block the opponent from winning
    char opponent = (player == 'X') ? 'O' : 'X';
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = opponent;
                if (isGameOver(board, opponent)) {
                    board[i][j] = player; // Block the opponent
                    return;
                }
                board[i][j] = ' '; // Undo the move
            }
        }
    }

    // Play in the center if available
    if (board[1][1] == ' ') {
        board[1][1] = player;
        return;
    }

    // Play in a corner if available
    int corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
    for (int i = 0; i < 4; i++) {
        int row = corners[i][0];
        int col = corners[i][1];
        if (board[row][col] == ' ') {
            board[row][col] = player;
            return;
        }
    }

    // Play in any available edge
    int edges[4][2] = {{0, 1}, {1, 0}, {1, 2}, {2, 1}};
    for (int i = 0; i < 4; i++) {
        int row = edges[i][0];
        int col = edges[i][1];
        if (board[row][col] == ' ') {
            board[row][col] = player;
            return;
        }
    }
}

int main() {
    char board[SIZE][SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    printf("Welcome to Tic-Tac-Toe!\n");

    int currentPlayer;
    printf("Who should play first? (1 for Human, 2 for Computer): ");
    scanf("%d", &currentPlayer);

    int row, col, moveCount = 0;
    int gameOver = 0;

    while (!gameOver) {
        printf("\n");

        if (currentPlayer == 1) {
            printf("Your turn (X):\n");
            printBoard(board);

            // Get the human player's move
            printf("Enter row (0, 1, or 2) and column (0, 1, or 2) separated by space: ");
            scanf("%d %d", &row, &col);

            if (isValidMove(board, row, col)) {
                board[row][col] = 'X';
                moveCount++;
                gameOver = isGameOver(board, 'X');
                currentPlayer = 2; // Switch to the computer player
            } else {
                printf("Invalid move. Try again.\n");
            }
        } else {
            printf("Computer's turn (O):\n");
            computerMove(board, 'O'); // Computer makes a strategic move
            moveCount++;
            printBoard(board);
            gameOver = isGameOver(board, 'O');
            currentPlayer = 1; // Switch to the human player
        }
    }

    if (gameOver == 1) {
        printBoard(board);
        printf("Player X wins! Congratulations!\n");
    } else {
        printBoard(board);
        printf("It's a draw! Good game!\n");
    }

    return 0;
}
