
#include "board.h"

int initalize_game(char board[][ROW_MAX +1][MESSAGE], int current_player)
{
    int x_coordinate, y_coordinate;
    char piece_colour[MESSAGE];

    current_player = PLAYER_WHITE;

    for (y_coordinate = ROW_MIN; y_coordinate <= ROW_MAX; y_coordinate++)
    {
        for (x_coordinate = COLUMN_MIN; x_coordinate <= COLUMN_MAX; x_coordinate++)
        {
            if (y_coordinate < 3) // y_coordinate is less than 3 so dealing with white pieces
            {
                strcpy(piece_colour, "w");
            }
            else if ((y_coordinate > 2) && (y_coordinate < 5))
            {
                strcpy(piece_colour, " ");
            }
            else // y_coordinate is 5 or more so dealing with black pieces
            {
                strcpy(piece_colour, "b");
            }
            update_board_array(board, piece_colour, x_coordinate, y_coordinate);
        }
    }
    return current_player;
}

void update_board_array(char board[][ROW_MAX +1][MESSAGE], char place_character[], int x_coordinate, int y_coordinate)
{
    if (((y_coordinate % 2 == 0) && (x_coordinate % 2 == 0)) || ((y_coordinate % 2 != 0) && (x_coordinate % 2 != 0)))
    {
        strcpy(board[x_coordinate][y_coordinate], place_character);
    }
    else
    {
        strcpy(board[x_coordinate][y_coordinate], INVALID_SQUARE);
    }
}

void clear_screen(void)
{
    printf("\033c");
}

void draw_board(char board[][ROW_MAX +1][MESSAGE], int current_player)
{
    int x_coordinate, y_coordinate;
    char temp_array[COLUMN_MAX + 1][ROW_MAX + 1][MESSAGE];

    if (current_player == PLAYER_BLACK)
    {
        for (y_coordinate = ROW_MIN; y_coordinate <= ROW_MAX; y_coordinate++)
        {
            for (x_coordinate = COLUMN_MAX; x_coordinate >= COLUMN_MIN; x_coordinate--)
            {
                strcpy(temp_array[x_coordinate][y_coordinate], board[x_coordinate][y_coordinate]);
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
                    current_player ? printf(" %d *   %s   *********   %s   *********   %s   *********   %s   *********\n", y_coordinate,
                                     temp_array[7-0][7-y_coordinate], temp_array[7-2][7-y_coordinate],
                                     temp_array[7-4][7-y_coordinate], temp_array[7-6][7-y_coordinate]) :
                             printf(" %d *   %s   *********   %s   *********   %s   *********   %s   *********\n", y_coordinate,
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
                    current_player ? printf(" %d *********   %s   *********   %s   *********   %s   *********   %s   *\n",y_coordinate,
                                     temp_array[7-1][7-y_coordinate], temp_array[7-3][7-y_coordinate],
                                     temp_array[7-5][7-y_coordinate], temp_array[7-7][7-y_coordinate]) :
                             printf(" %d *********   %s   *********   %s   *********   %s   *********   %s   *\n",y_coordinate,
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

bool validate_piece(char board[][ROW_MAX +1][MESSAGE], int current_player, int x_coordinate, int y_coordinate)
{
    if (current_player == PLAYER_WHITE)
    {
        return ((strcmp(board[x_coordinate][y_coordinate], "w") == 0) || (strcmp(board[x_coordinate][y_coordinate], "W") == 0)) ? true : false;
    }
    else
    {
        return ((strcmp(board[x_coordinate][y_coordinate], "b") == 0) || (strcmp(board[x_coordinate][y_coordinate], "B") == 0)) ? true : false;
    }
}

bool off_board(int x_coordinate, int y_coordinate)
{
    return (((x_coordinate >= COLUMN_MIN) && (x_coordinate <= COLUMN_MAX)) &&
            ((y_coordinate >= ROW_MIN) && (y_coordinate <= ROW_MAX))) ? false : true;
}

bool valid_square(char board[][ROW_MAX +1][MESSAGE], int x_coordinate, int y_coordinate)
{
    return (strcmp(board[x_coordinate][y_coordinate], EMPTY_SQUARE) == 0) ? true : false;
}

void get_coordinates(char board[][ROW_MAX +1][MESSAGE], bool run_before, int current_player, int *p_x, int *p_y)
{
    char starting_phrase[] = "Whites turn::";
    char phrase1[] = PHRASE1, phrase2[] = PHRASE3;

    current_player ? strcpy(starting_phrase, "Blacks turn::") : strcpy(starting_phrase, "Whites turn::");
    if (run_before == false)
    {
        strcpy(phrase1, PHRASE1);
        strcpy(phrase2, PHRASE2);
    }
    else
    {
        strcpy(phrase1, PHRASE3);
        strcpy(phrase2, PHRASE4);
    }
    while (1)
    {
        printf("%s %s", starting_phrase, phrase1);
        scanf(" %1d", &*p_x);
        if (*p_x == QUIT)
        {
            exit(0);
        }
        printf("%s %s", starting_phrase, phrase2);
        scanf(" %1d", &*p_y);
        if (current_player == PLAYER_BLACK)
        {
            *p_x = 7 - *p_x;
            *p_y = 7 - *p_y;
        }
        if (off_board(*p_x, *p_y) == false)
        {
            break;
        }
        printf("Co-ordinates are off the board\n");
    }
}
