#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ROW_MIN 0
#define ROW_MAX 7
#define COLUMN_MIN 0
#define COLUMN_MAX 7
#define INVALID_SQUARE '!'
#define QUIT 9

enum player { PLAYER_WHITE = 0, PLAYER_BLACK = 1 };

/************************************************************************
 *initialise game: Sets up a new game.                                  *
 ************************************************************************/

int initalize_game(char board[][ROW_MAX + 1], int current_player);

/************************************************************************
 * update board array: Updates the board array by putting the character *
 *                     passed to it at the position passed to it.       *
 ************************************************************************/

void update_board_array(char board[][ROW_MAX + 1], char place_character, int x_cordinate, int y_coordinate);

/************************************************************************
 * clear screen: Clears the screen so the board can be redrawn.         *
 ************************************************************************/

void clear_screen(void);

/************************************************************************
 * draw board: Draws a board on the screen using the board array to     *
 *             place the pieces.                                        *
 ************************************************************************/

void draw_board(char board[][ROW_MAX +1], int current_player);

/************************************************************************
 * get co-ordinates: Gets the co-ordinates of the piece first time run  *
 *                   gets the co-ordinates the player wants to move     *
 *                   thier piece to the second time run.                *
 ************************************************************************/

 void get_coordinates(char board[][ROW_MAX + 1], bool run_before, int current_player, int *p_x, int *p_y);

/************************************************************************
 * off board: Checks if the co-ordinates entered are valid or off the   *
 *            board.  Returns false if they are valid or true if they   *
 *            off the board.                                            *
 ************************************************************************/

bool off_board(int x_coordinate, int y_coordinate);

/************************************************************************
 * validate piece: Checks if a piece of the players colour is at the    *
 *                 given co-ordinates.  Returns true if there is or     *
 *                 false if there isn't.                                *
 ************************************************************************/

bool validate_piece(char board[][ROW_MAX + 1], int current_player, int x_coordinate, int y_coordinate);

/************************************************************************
 * valid square: Checks the co-ordinates to move the piece to is a valid*
 *               square ie isnt an illegal square or already occupied   *
 ************************************************************************/

bool valid_square(char board[][ROW_MAX + 1], int x_coordinate, int y_coordinate);
#endif // BOARD_H_INCLUDED
