#include <stdio.h>
#include <stdlib.h>

char board[8][8] = {
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {' ', '.', ' ', '.', ' ', '.', ' ', '.'},
    {'.', ' ', '.', ' ', '.', ' ', '.', ' '},
    {' ', '.', ' ', '.', ' ', '.', ' ', '.'},
    {'.', ' ', '.', ' ', '.', ' ', '.', ' '},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
};

int piece_value[6] = {100, 320, 330, 500, 900, 20000};
char piece_name[6] = {'P', 'N', 'B', 'R', 'Q', 'K'};

int evaluate_board() {
    int score = 0;
    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (board[i][j] == ' ') continue;
            int piece_index = 0;
            while (board[i][j] != piece_name[piece_index]) piece_index++;
            if (board[i][j] >= 'a' && board[i][j] <= 'z') {
                score -= piece_value[piece_index];
            } else {
                score += piece_value[piece_index];
            }
        }
    }
    return score;
}

int is_valid_move(int from_x, int from_y, int to_x, int to_y) {
    // Check if the move is within the board
    if (from_x < 0 || from_x > 7 || from_y < 0 || from_y > 7 || to_x < 0 || to_x > 7 || to_y < 0 || to_y > 7) {
        return 0;
    }
    // Check if the piece belongs to the player
    if (board[from_x][from_y] >= 'a' && board[from_x][from_y] <= 'z') {
        return 0;
    }
    // Check if the destination is not occupied by the player's piece
    if (board[to_x][to_y] >= 'A' && board[to_x][to_y] <= 'Z') {
        return 0;
    }
    // Check if the move is valid for the piece
    switch (board[from_x][from_y]) {
        case 'P':
            if (from_x == 1 && to_x == 3 && board[2][from_y] == ' ' && board[3][from_y] == ' ') {
                return 1;
            }
            if (to_x == from_x + 1 && to_y == from_y && board[to_x][to_y] == ' ') {
                return 1;
            }
            if (to_x == from_x + 1 && abs(to_y - from_y) == 1 && board[to_x][to_y] >= 'A' && board[to_x][to_y] <= 'Z') {
                return 1;
            }
            break;
        case 'N':
            if ((abs(to_x - from_x) == 2 && abs(to_y - from_y) == 1) || (abs(to_x - from_x) == 1 && abs(to_y - from_y) == 2)) {
                return 1;
            }
            break;
        case 'B':
            if (abs(to_x - from_x) == abs(to_y - from_y)) {
                int x_dir = (to_x - from_x) / abs(to_x - from_x);
                int y_dir = (to_y - from_y) / abs(to_y - from_y);
                int x = from_x + x_dir;
                int y = from_y + y_dir;
                while (x != to_x && y != to_y) {
                    if (board[x][y] != ' ') {
                        return 0;
                    }
                    x += x_dir;
                    y += y_dir;
                }
                return 1;
            }
            break;
        case 'R':
            if (to_x == from_x) {
                int y_dir = (to_y - from_y) / abs(to_y - from_y);
                int y = from_y + y_dir;
                while (y != to_y) {
                    if (board[from_x][y] != ' ') {
                        return 0;
                    }
                    y += y_dir;
                }
                return 1;
            }
            if (to_y == from_y) {
                int x_dir = (to_x - from_x) / abs(to_x - from_x);
                int x = from_x + x_dir;
                while (x != to_x) {
                    if (board[x][from_y] != ' ') {
                        return 0;
                    }
                    x += x_dir;
                }
                return 1;
            }
            break;
        case 'Q':
            if (abs(to_x - from_x) == abs(to_y - from_y)) {
                int x_dir = (to_x - from_x) / abs(to_x - from_x);
                int y_dir = (to_y - from_y) / abs(to_y - from_y);
                int x = from_x + x_dir;
                int y = from_y + y_dir;
                while (x != to_x && y != to_y) {
                    if (board[x][y] != ' ') {
                        return 0;
                    }
                    x += x_dir;
                    y += y_dir;
                }
                return 1;
            }
            if (to_x == from_x) {
                int y_dir = (to_y - from_y) / abs(to_y - from_y);
                int y = from_y + y_dir;
                while (y != to_y) {
                    if (board[from_x][y] != ' ') {
                        return 0;
                    }
                    y += y_dir;
                }
                return 1;
            }
            if (to_y == from_y) {
                int x_dir = (to_x - from_x) / abs(to_x - from_x);
                int x = from_x + x_dir;
                while (x != to_x) {
                    if (board[x][from_y] != ' ') {
                        return 0;
                    }
                    x += x_dir;
                }
                return 1;
            }
            break;
        case 'K':
            if (abs(to_x - from_x) <= 1 && abs(to_y - from_y) <= 1) {
                return 1;
            }
            break;
    }
    return 0; // If no valid move conditions were met, return 0
}

int main() {
    int initial_score = evaluate_board();
    printf("Initial board evaluation score: %d\n", initial_score);

    // Test some moves
    int from_x = 6, from_y = 4, to_x = 4, to_y = 4; // Example move: Pawn moving two squares forward
    if (is_valid_move(from_x, from_y, to_x, to_y)) {
        printf("Move is valid!\n");
    } else {
        printf("Move is invalid!\n");
    }

    from_x = 7, from_y = 1, to_x = 5, to_y = 2; // Example move: Knight
    if (is_valid_move(from_x, from_y, to_x, to_y)) {
        printf("Move is valid!\n");
    } else {
        printf("Move is invalid!\n");
    }

    // Add more test cases here...

    return 0;
}

