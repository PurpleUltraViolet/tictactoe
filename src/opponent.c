#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "opponent.h"

void opponentturn(void) {
    int nummoves = 0, move;
    int moves[9];
    int cbestscore = -100, tscore;
    int nb[9];
    for(int i = 0; i < 9; i++) {
        nb[i] = board[i];
    }

    for(int i = 0; i < 9; i++) {
        if(nb[i] == 0) {
            nb[i] = opponent;
            tscore = minimax(nb, 1, 0);
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

int minimax(int *b, int shouldmin, int crecdepth) {
    crecdepth++;
    int boardcheck = board_check(b);
    if(boardcheck == opponent)
        return 10 - crecdepth;
    if(boardcheck == player)
        return crecdepth - 10;
    else if(boardcheck == 0)
        return 0;

    int toadd = shouldmin ? player : opponent;
    int cbestscore = shouldmin ? 5 : -5, tbestscore;
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
            tbestscore = minimax(nb, !shouldmin, crecdepth);
            if(shouldmin && tbestscore < cbestscore) cbestscore = tbestscore;
            if(!shouldmin && tbestscore > cbestscore) cbestscore = tbestscore;
            nb[i] = 0;
        }
    }

    free(nb);
    return cbestscore;
}
