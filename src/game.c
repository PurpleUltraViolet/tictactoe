#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "opponent.h"
#include "game.h"

void playerturn(void) {
    int move = 0;
    size_t bufsize = 0; ssize_t insize;
    char *buf = NULL;
    do {
        printf("Where do you want to put your %c? ",
                player == X_VAL ? 'X' : 'O');
        insize = getline(&buf, &bufsize, stdin);
        if(insize == -1) {
            free(buf);
            exit(0);
        }
        sscanf(buf, "%d", &move);
        move -= 1;
    } while((move < 0 || move > 8) || board[move] != 0);
    board[move] = player;
}

int gameloop(int start) {
    int rval;
    if(start == 'p')
        goto playerstart;
    else
        goto opponentstart;

    while(1) {
playerstart:
        board_draw();
        playerturn();
        rval = board_check(board);
        if(rval != 2) break;
opponentstart:
        board_draw();
        opponentturn();
        rval = board_check(board);
        if(rval != 2) break;
    }

    return rval;
}
