
#include "board.h"

int initalize_game(char board[][ROW_MAX + 1], int current_player)
{
    int x_coordinate, y_coordinate;
    char piece_colour;

    current_player = PLAYER_WHITE;

    for (y_coordinate = ROW_MIN; y_coordinate <= ROW_MAX; y_coordinate++)
    {
        for (x_coordinate = COLUMN_MIN; x_coordinate <= COLUMN_MAX; x_coordinate++)
        {
            if (y_coordinate < 3) // y_coordinate is less than 3 so dealing with white pieces
            {
                piece_colour = 'w';
                update_board_array(board, piece_colour, x_coordinate, y_coordinate);
            }
            else if ((y_coordinate > 2) && (y_coordinate < 5))
            {
                piece_colour = ' '; //a space
                update_board_array(board, piece_colour, x_coordinate, y_coordinate);
            }
            else // y_coordinate is 5 or more so dealing with black pieces
            {
                piece_colour = 'b';
                update_board_array(board, piece_colour, x_coordinate, y_coordinate);
            }
        }
    }
    return current_player;
}

void update_board_array(char board[][ROW_MAX + 1], char place_character, int x_coordinate, int y_coordinate)
{
    board[x_coordinate][y_coordinate] = (((y_coordinate % 2 == 0) && (x_coordinate % 2 == 0)) ||
                                         ((y_coordinate % 2 != 0) && (x_coordinate % 2 != 0))) ? place_character : INVALID_SQUARE;
}

void clear_screen(void)
{
    printf("\033c");
}

void draw_board(char board[][ROW_MAX + 1], int current_player)
{
    int x_coordinate, y_coordinate;
    char temp_array[COLUMN_MAX + 1][ROW_MAX + 1];

    if (current_player == 1)
    {
        for (y_coordinate = ROW_MIN; y_coordinate <= ROW_MAX; y_coordinate++)
        {
            for (x_coordinate = COLUMN_MAX; x_coordinate >= COLUMN_MIN; x_coordinate--)
            {
                temp_array[x_coordinate][y_coordinate] = board[x_coordinate][y_coordinate];
            }
        }
    }

    for (y_coordinate = ROW_MAX; y_coordinate >= ROW_MIN; y_coordinate--)
    {
        for (x_coordinate = COLUMN_MIN; x_coordinate <= 3; x_coordinate++)
        {
            if (x_coordinate == 0)
            {
                printf("   *****************************************************************\n");
            }
            else if (y_coordinate % 2 == 0)
            {
                if (x_coordinate % 2 == 0)
                {
                    current_player ? printf(" %d *   %c   *********   %c   *********   %c   *********   %c   *********\n", y_coordinate,
                                     temp_array[7-0][7-y_coordinate], temp_array[7-2][7-y_coordinate],
                                     temp_array[7-4][7-y_coordinate], temp_array[7-6][7-y_coordinate]) :
                             printf(" %d *   %c   *********   %c   *********   %c   *********   %c   *********\n", y_coordinate,
                             board[0][y_coordinate], board[2][y_coordinate], board[4][y_coordinate], board[6][y_coordinate]);
                }
                else
                {
                    printf("   *       *********       *********       *********       *********\n");
                }
            }
            else
            {
                if (x_coordinate % 2 == 0)
                {
                    current_player ? printf(" %d *********   %c   *********   %c   *********   %c   *********   %c   *\n",y_coordinate,
                                     temp_array[7-1][7-y_coordinate], temp_array[7-3][7-y_coordinate],
                                     temp_array[7-5][7-y_coordinate], temp_array[7-7][7-y_coordinate]) :
                             printf(" %d *********   %c   *********   %c   *********   %c   *********   %c   *\n",y_coordinate,
                             board[1][y_coordinate], board[3][y_coordinate], board[5][y_coordinate], board[7][y_coordinate]);
                }
                else
                {
                    printf("   *********       *********       *********       *********       *\n");
                }
            }
        }
    }
    printf("   *****************************************************************\n");
    printf("       0        1       2      3       4       5       6       7    \n");
}

bool validate_piece(char board[][ROW_MAX + 1], int current_player, int x_coordinate, int y_coordinate)
{
    if (current_player == PLAYER_WHITE)
    {
        return ((board[x_coordinate][y_coordinate] == 'w') || (board[x_coordinate][y_coordinate] == 'W')) ? true : false;
    }
    else
    {
        return ((board[x_coordinate][y_coordinate] == 'b') || (board[x_coordinate][y_coordinate] == 'B')) ? true : false;
    }
}

bool off_board(int x_coordinate, int y_coordinate)
{
    return (((x_coordinate >= COLUMN_MIN) && (x_coordinate <= COLUMN_MAX)) &&
            ((y_coordinate >= ROW_MIN) && (y_coordinate <= ROW_MAX))) ? false : true;
}

bool valid_square(char board[][ROW_MAX + 1], int x_coordinate, int y_coordinate)
{
    return (board[x_coordinate][y_coordinate] = ' ') ? true : false;
}

void get_coordinates(char board[][ROW_MAX + 1], bool run_before, int current_player, int *p_x, int *p_y)
{
    //int x_coordinate_of_piece, y_coordinate_of_piece, x_coordinate_to_move_to, y_coordinate_to_move_to;
    char starting_phrase[] = "Whites turn::";

    current_player ? strcpy(starting_phrase, "Blacks turn::") : strcpy(starting_phrase, "Whites turn::");
    if (run_before == false)
    {
        printf("%s Please enter the x co-ordinate of the piece you wish to move (0-7) or 9 to surrender: ", starting_phrase);
        scanf(" %1d", &*p_x);
        if (*p_x == QUIT)
        {
            exit(0);
        }
        printf("%s Please enter the y co-ordinate of the piece you wish to move (0-7): ", starting_phrase);
        scanf(" %1d", &*p_y);
        if (current_player == PLAYER_BLACK)
        {
            *p_x -= 7;
            *p_y -= 7;
        }
    }
    else
    {
        printf("%s Please enter the x co-ordinate of the place you wish to move to (0-7): ", starting_phrase);
        scanf(" %1d", &*p_x);
        printf("%s Please enter the y co-ordinate of the place you wish to move to (0-7): ", starting_phrase);
        scanf(" %1d", &*p_y);
        if (current_player == PLAYER_BLACK)
        {
            *p_x -= 7;
            *p_y -= 7;
        }
    }
}