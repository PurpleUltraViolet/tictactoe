#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "board.h"
#include "opponent.h"

void opponentturn(void) {
    int nummoves = 0, move;
    int moves[9];
    int cbestscore = INT_MIN, tscore;
    int nb[9];
    for(int i = 0; i < 9; i++) {
        nb[i] = board[i];
    }

    for(int i = 0; i < 9; i++) {
        if(nb[i] == 0) {
            nb[i] = opponent;
            tscore = minimax(nb, 1, INT_MIN, INT_MAX, 0);
            if(tscore > cbestscore) {
                cbestscore = tscore;
                moves[0] = i;
                nummoves = 1;
            }
            if(tscore == cbestscore)
                moves[nummoves++] = i;
            nb[i] = 0;
        }
    }

    move = moves[rand() % nummoves];
    board[move] = opponent;
    printf("I place %c on %d\n", opponent == O_VAL ? 'O' : 'X', move + 1);
}

int minimax(int *b, int shouldmin, int oalpha, int obeta, int depth) {
    int alpha = oalpha, beta = obeta;
    depth++;
    int boardcheck = board_check(b);
    if(boardcheck == opponent)
        return 10 - depth;
    if(boardcheck == player)
        return depth - 10;
    else if(boardcheck == 0)
        return 0;

    int toadd = shouldmin ? player : opponent;
    int value = shouldmin ? INT_MAX : INT_MIN, tvalue;
    int *nb = malloc(sizeof(int) * 9);
    if(!nb) {
        fprintf(stderr, "Ran out of memory!\n");
        exit(2);
    }
    for(int i = 0; i < 9; i++) {
        nb[i] = b[i];
    }

    for(int i = 0; i < 9; i++) {
        if(nb[i] == 0) {
            nb[i] = toadd;
            tvalue = minimax(nb, !shouldmin, alpha, beta, depth);
            if(shouldmin) {
                if(tvalue < value) value = tvalue;
                beta = beta < value ? beta : value;
                if(beta <= alpha) break;
            } else {
                if(tvalue > value) value = tvalue;
                alpha = alpha > value ? alpha : value;
                if(alpha >= beta) break;
            }
            nb[i] = 0;
        }
    }

    free(nb);
    return value;
}
