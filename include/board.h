#ifndef BOARD_H_
#define BOARD_H_

/* Does't actually matter which is which, just needs 1 and -1 */
#define X_VAL 1
#define O_VAL -1

/* Global board */
extern int board[9];

/* Player */
extern int player;
extern int opponent;

/* Checks board
 * Returns defined values for win states, 0 for draw, and 2 for none */
int board_check(int *b);

/* Outputs board */
void board_draw(void);

#endif
