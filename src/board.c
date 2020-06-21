#include <stdio.h>
#include "board.h"

int board[9] = {0};

int player = X_VAL;
int opponent = O_VAL;

int board_check(int *b) {
    int winner = 0, drawpossible = 1, cstate, i, j, k, count;

    for(i = 0; i < 9; i++) {
        if(b[i] == 0) drawpossible = 0;
    }

    /* Check both players */
    for(cstate = X_VAL, i = 0; i < 2; i++, cstate *= -1) {
        /* Vertical check */
        for(j = 0; j < 3; j++) {
            count = 0;
            for(k = 0; k < 3; k++) {
                if(b[j + k * 3] == cstate) count++;
            }
            if(count == 3) {
                winner = cstate;
                goto END;
            }
        }

        /* Horizontal check */
        for(j = 0; j < 3; j++) {
            count = 0;
            for(k = 0; k < 3; k++) {
                if(b[k + j * 3] == cstate) count++;
            }
            if(count == 3) {
                winner = cstate;
                goto END;
            }
        }

        /* Diagonal check */
        count = 0;
        for(j = 0; j < 3; j++) {
            if(b[j + j * 3] == cstate) count++;
        }
        if(count == 3) {
            winner = cstate;
            goto END;
        }
        count = 0;
        for(j = 0; j < 3; j++) {
            if(b[(2 - j) + j * 3] == cstate) count++;
        }
        if(count == 3) {
            winner = cstate;
            goto END;
        }
    }

    if(winner == 0 && !drawpossible) return 2;
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
           "%c | %c | %c\t1 | 2 | 3\n"
           "--+---+--\t--+---+--\n"
           "%c | %c | %c\t4 | 5 | 6\n"
           "--+---+--\t--+---+--\n"
           "%c | %c | %c\t7 | 8 | 9\n"
           "\n",
           boardchars[0], boardchars[1], boardchars[2],
           boardchars[3], boardchars[4], boardchars[5],
           boardchars[6], boardchars[7], boardchars[8]);
}
