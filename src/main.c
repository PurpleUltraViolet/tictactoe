#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "game.h"

int main(int argc, char **argv) {
    if(argc >= 2) {
        switch(argv[1][0]) {
        case 'x':
        case 'X':
            player = X_VAL;
            opponent = O_VAL;
            break;

        case 'o':
        case 'O':
            player = O_VAL;
            opponent = X_VAL;
            break;

        default:
            fprintf(stderr, "Usage: %s [x|o]\n"
                    "Where the optional argument indicates the player "
                    "character\n", argv[0]);
            exit(1);
        }
    } else {
        srand(time(NULL));
        player = rand() % 2 ? X_VAL : O_VAL;
        opponent = player * -1;
    }

    int winner = gameloop(player == X_VAL ? 'p' : 'o');
    board_draw();
    if(winner == player) {
        printf("You win!\n");
    } else if(winner == opponent) {
        printf("You lose!\n");
    } else {
        printf("It's a draw!\n");
    }
    return 0;
}
