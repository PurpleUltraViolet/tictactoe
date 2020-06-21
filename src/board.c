#include <stdio.h>
#include "board.h"

int board[9] = {0};

int player = X_VAL;
int opponent = O_VAL;

int board_check(int *b) {
    static int winpos[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 3, 6, 1, 4, 7, 2,
        5, 8, 0, 4, 8, 2, 4, 6};
    int winner = 0, drawpossible = 1, i;

    for(i = 0; i < 9; i++) {
        if(b[i] == 0) drawpossible = 0;
    }

    /* Check both players */
    for(i = 0; i < 24; i += 3) {
        if(b[winpos[i]] == X_VAL && b[winpos[i + 1]] == X_VAL &&
                b[winpos[i + 2]] == X_VAL) {
            winner = X_VAL;
            goto END;
        }
    }
    for(i = 0; i < 24; i += 3) {
        if(b[winpos[i]] == O_VAL && b[winpos[i + 1]] == O_VAL &&
                b[winpos[i + 2]] == O_VAL) {
            winner = O_VAL;
            goto END;
        }
    }

    if(!drawpossible) return 2;
END:
    return winner;
}

void board_draw(void) {
    static char boardchars[9];
    for(int i = 0; i < 9; i++) {
        boardchars[i] = (board[i] == X_VAL ? 'X' :
                (board[i] == O_VAL ? 'O' : ' '));
    }
    printf("\n"
           " %c | %c | %c \t 1 | 2 | 3 \n"
           "---+---+---\t---+---+---\n"
           " %c | %c | %c \t 4 | 5 | 6 \n"
           "---+---+---\t---+---+---\n"
           " %c | %c | %c \t 7 | 8 | 9 \n"
           "\n",
           boardchars[0], boardchars[1], boardchars[2],
           boardchars[3], boardchars[4], boardchars[5],
           boardchars[6], boardchars[7], boardchars[8]);
}
