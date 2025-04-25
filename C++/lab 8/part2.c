#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include "lab8part2.h"
#include "liblab8part2.h"

#define MAX_SIZE 26
#define MAX_DEPTH 5 
#define CORNER_BONUS 50
#define EDGE_BONUS 10
#define STABLE_DISK_BONUS 20

// printBoard
void printBoard(char board[][MAX_SIZE], int n) {
    // print column headers
    printf("  ");
    for (char c = 'a'; c < 'a' + n; c++) {
        printf("%c", c);
    }
    printf("\n");

    // print each row (row label + row contents)
    for (int i = 0; i < n; i++) {
        printf("%c ", (char)('a' + i));
        for (int j = 0; j < n; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

// positionInBounds
bool positionInBounds(int n, int row, int col) {
    return (row >= 0 && row < n && col >= 0 && col < n);
}

// checkLegalInDirection
// returns true if placing `color` at (row, col) flips at least one
// line of opponent tiles in the (deltaRow, deltaCol) direction.
bool checkLegalInDirection(char board[][MAX_SIZE],
                           int n,
                           int row, int col,
                           char color,
                           int deltaRow, int deltaCol) {
    char opponent = (color == 'W') ? 'B' : 'W';
    int r = row + deltaRow;
    int c = col + deltaCol;

    // first step must be on board and be opponent's tile
    if (!positionInBounds(n, r, c) || board[r][c] != opponent) {
        return false;
    }

    // move forward until leave board or find a non-opponent tile
    while (positionInBounds(n, r, c) && board[r][c] == opponent) {
        r += deltaRow;
        c += deltaCol;
    }

    // must be on board and find our own color
    if (positionInBounds(n, r, c) && board[r][c] == color) {
        return true;
    }
    return false;
}

// findAvailableMoves
void findAvailableMoves(char board[][MAX_SIZE], int n, char color) {

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (board[r][c] == 'U') {
                // check all 8 directions
                for (int dr = -1; dr <= 1; dr++) {
                    for (int dc = -1; dc <= 1; dc++) {
                        if (dr == 0 && dc == 0) {
                            continue;
                        }
                        if (checkLegalInDirection(board, n, r, c, color, dr, dc)) {
                            //print the first valid direction and skip to next cell
                            printf("%c%c\n", (char)('a' + r), (char)('a' + c));
                            goto NEXT_SPOT;
                        }
                    }
                }
            }
NEXT_SPOT:;
        }
    }
}

// makeMove
// places a tile of `color` at (row, col), then flips
// all lines of opponent tiles in directions that are valid to flip.
void applyMove(char board[][MAX_SIZE],
    int n,
    char color,
    int row, int col) {
board[row][col] = color;  // place tile
char opponent = (color == 'W') ? 'B' : 'W';

// for all 8 directions, flip if checkLegalInDirection says so
for (int dr = -1; dr <= 1; dr++) {
for (int dc = -1; dc <= 1; dc++) {
  if (dr == 0 && dc == 0) continue;
  if (checkLegalInDirection(board, n, row, col, color, dr, dc)) {
      int r = row + dr;
      int c = col + dc;
      while (board[r][c] == opponent) {
          board[r][c] = color;
          r += dr;
          c += dc;
      }
  }
}
}
}

// calculate how many opponent pieces can be flipped if placing a piece of color at (row, col)
int computeFlipCount(char board[][MAX_SIZE], int n, int row, int col, char color) {
    if (board[row][col] != 'U') {
        return 0;
    }
    char opponent = (color == 'W') ? 'B' : 'W';
    int totalFlips = 0;

    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            if (checkLegalInDirection(board, n, row, col, color, dr, dc)) {
                int r = row + dr;
                int c = col + dc;
                int flips = 0;
                while (board[r][c] == opponent) {
                    flips++;
                    r += dr;
                    c += dc;
                }
                totalFlips += flips;
            }
        }
    }
    return totalFlips;
}

// choose the position that flips the most opponent pieces; if there is a tie, choose the one with the smallest row and column
bool computerMove(char board[][MAX_SIZE], int n, char compColor) {
    int bestScore = 0;
    int bestRow = -1;
    int bestCol = -1;

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            int flips = computeFlipCount(board, n, r, c, compColor);
            if (flips > bestScore) {
                bestScore = flips;
                bestRow = r;
                bestCol = c;
            }
        }
    }
    if (bestScore == 0) {
        return false;
    }

    applyMove(board, n, compColor, bestRow, bestCol);
    printf("Computer places %c at %c%c.\n",
           compColor,
           (char)('a' + bestRow),
           (char)('a' + bestCol));
    return true;
}

// count the number of B and W pieces currently on the board
void countPieces(char board[][MAX_SIZE], int n, int *bCount, int *wCount) {
    *bCount = 0;
    *wCount = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (board[r][c] == 'B') (*bCount)++;
            else if (board[r][c] == 'W') (*wCount)++;
        }
    }
}

// ============================================================================
static int evaluate(char b[][26], int size, char player) {
    int score = 0;
    const char opponent = (player == 'W') ? 'B' : 'W';

    static int weights[8][8] = {
        {100, -20, 10, 5, 5, 10, -20, 100},
        {-20, -50, -2, -2, -2, -2, -50, -20},
        {10, -2, 5, 1, 1, 5, -2, 10},
        {5, -2, 1, 0, 0, 1, -2, 5},
        {5, -2, 1, 0, 0, 1, -2, 5},
        {10, -2, 5, 1, 1, 5, -2, 10},
        {-20, -50, -2, -2, -2, -2, -50, -20},
        {100, -20, 10, 5, 5, 10, -20, 100}
    };

    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (b[r][c] == player) {
                score += (size == 8) ? weights[r][c] : 1;
            } else if (b[r][c] == opponent) {
                score -= (size == 8) ? weights[r][c] : 1;
            }
        }
    }

    const int corners[4][2] = {{0, 0}, {0, size - 1}, {size - 1, 0}, {size - 1, size - 1}};
    for (int i = 0; i < 4; i++) {
        int r = corners[i][0], c = corners[i][1];
        if (b[r][c] == player) score += CORNER_BONUS;
    }

    int mobility = 0;
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (b[r][c] == 'U') {
                mobility += computeFlipCount(b, size, r, c, player);
            }
        }
    }
    score += mobility / 2;

    return score;
}

static int alphabeta(char b[][26], int depth, int alpha, int beta,
                     char currentPlayer, bool maximizingPlayer, int size) {
    if (depth == 0) {
        return evaluate(b, size, maximizingPlayer ? currentPlayer : (currentPlayer == 'W' ? 'B' : 'W'));
    }

    int bestValue = maximizingPlayer ? INT_MIN : INT_MAX;
    const char opponent = (currentPlayer == 'W') ? 'B' : 'W';

    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (b[r][c] != 'U') continue;

            int flips = computeFlipCount(b, size, r, c, currentPlayer);
            if (flips <= 0) continue;

            char newBoard[26][26];
            memcpy(newBoard, b, sizeof(char) * 26 * 26);
            applyMove(newBoard, size, currentPlayer, r, c);

            int value = alphabeta(newBoard, depth - 1, alpha, beta, opponent, !maximizingPlayer, size);

            if (maximizingPlayer) {
                if (value > bestValue) bestValue = value;
                if (bestValue > alpha) alpha = bestValue;
            } else {
                if (value < bestValue) bestValue = value;
                if (bestValue < beta) beta = bestValue;
            }

            if (beta <= alpha) break;
        }
        if (beta <= alpha) break;
    }

    return bestValue;
}

int makeMove(const char board[][26], int n, char turn, int *row, int *col) {
    int bestVal = INT_MIN;
    *row = *col = -1;

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (board[r][c] != 'U') continue;

            int flips = computeFlipCount(board, n, r, c, turn);
            if (flips <= 0) continue;

            char tempBoard[26][26];
            memcpy(tempBoard, board, sizeof(char) * 26 * 26);
            applyMove(tempBoard, n, turn, r, c);

            int value = alphabeta(tempBoard, MAX_DEPTH, INT_MIN, INT_MAX,
                                  (turn == 'W') ? 'B' : 'W', false, n);

            if (value > bestVal || (value == bestVal && (r < *row || (r == *row && c < *col)))) {
                bestVal = value;
                *row = r;
                *col = c;
            }
        }
    }

    return (*row != -1);
}
//============================================================================

int main(void) {
    int n;
    static char board[MAX_SIZE][MAX_SIZE];
    char compColor; 
    char humanColor;

    printf("Enter the board dimension: ");
    scanf("%d", &n);
    printf("Computer plays (B/W) : ");
    scanf(" %c", &compColor);

    // initialize the board
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = 'U';
        }
    }

    if (n % 2 == 0) {
        int mid = n / 2 - 1;
        board[mid][mid]         = 'W';
        board[mid][mid + 1]     = 'B';
        board[mid + 1][mid]     = 'B';
        board[mid + 1][mid + 1] = 'W';
    }

    // display the board with the initial game setup
    printBoard(board, n);


    // if the computer is B, then the player is W; otherwise, vice versa
    if (compColor == 'B') {
        humanColor = 'W';
    } else {
        humanColor = 'B';
    }

    // default B first
    // if you want the computer to go first when it's 'W', check compColor == 'W' here
    char currentPlayer = 'B';

    // multi-turn loop
    while (1) {
        // check if the current player has any valid moves
        bool curPlayerCanMove = false;
        for (int r = 0; r < n && !curPlayerCanMove; r++) {
            for (int c = 0; c < n && !curPlayerCanMove; c++) {
                if (computeFlipCount(board, n, r, c, currentPlayer) > 0) {
                    curPlayerCanMove = true;
                }
            }
        }
    
        // check if the opponent has any valid moves
        char otherPlayer = (currentPlayer == 'B') ? 'W' : 'B';
        bool otherPlayerCanMove = false;
        for (int r = 0; r < n && !otherPlayerCanMove; r++) {
            for (int c = 0; c < n && !otherPlayerCanMove; c++) {
                if (computeFlipCount(board, n, r, c, otherPlayer) > 0) {
                    otherPlayerCanMove = true;
                }
            }
        }
    
        if (!curPlayerCanMove && !otherPlayerCanMove) {
            // both players have no valid moves
            break;
        }
    
        if (!curPlayerCanMove) {
            // current player also has no valid moves
            printf("%c player has no valid move.\n", currentPlayer);
        } else {
            // a valid move is available
            if (currentPlayer == compColor) {
                // the computer make its move
                bool ok = computerMove(board, n, compColor);
                if (!ok) {
                    // this scenario is unlikely, but included as a safeguard
                    printf("%c player has no valid move.\n", compColor);
                } else {
                    // success, print down the board
                    printBoard(board, n);
                }
            } else {
                // human player makes a move
                printf("Enter move for colour %c (RowCol): ", humanColor);
                char rowChar, colChar;
                scanf(" %c%c", &rowChar, &colChar);
    
                int rr = rowChar - 'a';
                int cc = colChar - 'a';
                int flips = computeFlipCount(board, n, rr, cc, humanColor);
                if (flips <= 0) {
                    printf("Invalid move.\n");
                    printf("%c player wins.\n", compColor);
                    return 0;
                } else {
                    applyMove(board, n, humanColor, rr, cc);
                    // success, print down the board
                    printBoard(board, n);
                }
            }
        }
        currentPlayer = otherPlayer;
    }
    
        
    // determine the winner
    int bCount, wCount;
    countPieces(board, n, &bCount, &wCount);
    if (bCount > wCount) {
        printf("B player wins.\n");
    } else if (wCount > bCount) {
        printf("W player wins.\n");
    } else {
        printf("Draw!\n");
    }

    return 0;
}


 
