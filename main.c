#include "board.h"

bool check_king(char board[][ROW_MAX + 1][MESSAGE], int current_player, int x_coordinate, int y_coordinate);
bool calculate_move(char board[][ROW_MAX +1][MESSAGE], bool is_king, int current_player, int piece_coordinate_x,
                    int piece_coordinate_y, int move_coordinate_x, int move_coordinate_y);
void move_1_square(char board[][ROW_MAX +1][MESSAGE], char character[], int piece_coordinate_x,
                    int piece_coordinate_y, int move_coordinate_x, int move_coordinate_y, int current_player);
int next_player(int current_player);
void colour_selected_piece(char board[][ROW_MAX + 1][MESSAGE], char code[], int current_player, int x, int y);
bool take_piece(char board[][ROW_MAX + 1][MESSAGE], bool is_king, int piece_coordinate_x, int piece_coordinate_y,
                                                    int move_coordinate_x, int move_coordinate_y, int current_player);
void count_pieces(char board[][ROW_MAX + 1][MESSAGE], int *p_number_of_white_pieces, int *p_number_of_black_pieces);
void move_test(char board[][ROW_MAX + 1][MESSAGE]);
void game_over(int current_player);

int main()
{
    enum player current_player = PLAYER_WHITE;
    char board[COLUMN_MAX + 1][ROW_MAX + 1][MESSAGE], code[ESCAPE_CODE], error_message[ERROR_MESSAGE];
    char *p_make_king;
    int x_coordinate_of_piece, y_coordinate_of_piece, x_coordinate_to_move_to, y_coordinate_to_move_to;
    int number_of_white_pieces_left, number_of_black_pieces_left;
    bool is_king = false;

    current_player = initalize_game(board, current_player);
    clear_screen();
    draw_board(board, current_player);
    move_test(board);
    current_player = PLAYER_WHITE;
    for(;;)
    {
        while (1)
        {
            strcpy(error_message, "");
            get_coordinates(board, false, current_player, &x_coordinate_of_piece, &y_coordinate_of_piece);
            if (validate_piece(board, current_player, x_coordinate_of_piece, y_coordinate_of_piece) == true)
            {
                strcpy(code, COLOUR_PIECE);
                colour_selected_piece(board, code, current_player, x_coordinate_of_piece, y_coordinate_of_piece);
                get_coordinates(board, true, current_player, &x_coordinate_to_move_to, &y_coordinate_to_move_to);
                if (valid_square(board, x_coordinate_to_move_to, y_coordinate_to_move_to) == true)
                {
                    is_king = check_king(board, current_player, x_coordinate_of_piece, y_coordinate_of_piece);
                    if (calculate_move(board, is_king, current_player, x_coordinate_of_piece, y_coordinate_of_piece,
                                      x_coordinate_to_move_to, y_coordinate_to_move_to) == true)
                    {
                        break;
                    }
                    else
                    {
                        strcpy(error_message, "invalid move\n");
                    }
                }
                else
                {
                    strcpy(error_message, "invalid square\n");
                }
            }
            else
            {
                strcpy(error_message, "no piece of your colour");
            }
            if (strlen(error_message) != 0)
            {
                if ((strcmp(error_message, "no piece of your colour")) == 0)
                {
                    printf("%s at co-ordinates %d,%d\n", error_message, x_coordinate_of_piece, y_coordinate_of_piece);
                }
                else
                {
                    strcpy(code, CLEAR_COLOUR);
                    colour_selected_piece(board,code, current_player, x_coordinate_of_piece, y_coordinate_of_piece);
                    printf("%s", error_message);
                }
            }
        }
        if ((current_player == PLAYER_WHITE && y_coordinate_to_move_to == ROW_MAX) ||
            (current_player == PLAYER_BLACK && y_coordinate_to_move_to == ROW_MIN))
        {
            p_make_king = current_player ? "B" : "W";
            update_board_array(board, p_make_king, x_coordinate_to_move_to, y_coordinate_to_move_to);
        }
        if (number_of_white_pieces_left == 0 || number_of_black_pieces_left == 0)
        {
            game_over(current_player);
        }
        current_player = next_player(current_player);
        clear_screen();
        draw_board(board, current_player);
        count_pieces(board, &number_of_white_pieces_left, &number_of_black_pieces_left);

    }
    return 0;
}

bool check_king(char board[][ROW_MAX + 1][MESSAGE], int current_player, int x_coordinate, int y_coordinate)
{
    char *p_king_label = current_player ? "B" : "W";
    char *position_ptr = strstr(board[x_coordinate][y_coordinate], p_king_label);

    //position = position_ptr == NULL ? false : true;

    //return position;
    return position_ptr != NULL;
}

bool calculate_move(char board[][ROW_MAX +1][MESSAGE], bool is_king, int current_player, int piece_coordinate_x,
                    int piece_coordinate_y, int move_coordinate_x, int move_coordinate_y)
{
    int difference_in_x_coordinate = piece_coordinate_x - move_coordinate_x;
    int difference_in_y_coordinate = current_player ? (piece_coordinate_y - move_coordinate_y) : (move_coordinate_y - piece_coordinate_y);
    char *p_player_label = is_king ? current_player ? "B" : "W" : current_player ? "b" : "w";

    if (difference_in_y_coordinate < 0 && is_king == false)//check the piece is moving in the right direction
    {
        return false;
    }
    else
    {
        if ((is_king == true || difference_in_y_coordinate == 1) && (difference_in_x_coordinate == -1 || difference_in_x_coordinate == 1)) //(((difference_in_x_coordinate == 1) || (difference_in_x_coordinate == -1)) && (difference_in_y_coordinate == 1))
        {
            move_1_square(board, p_player_label, piece_coordinate_x, piece_coordinate_y, move_coordinate_x,
                                                                     move_coordinate_y, current_player);
            return true;
        }
        else
        {
            if (take_piece(board, is_king, piece_coordinate_x, piece_coordinate_y, move_coordinate_x, move_coordinate_y, current_player) == true)
            {
                return true;
            }
            else
            {
                return false;
            }

        }
    }
}

void move_1_square(char board[][ROW_MAX +1][MESSAGE], char character[], int piece_coordinate_x,int piece_coordinate_y, int move_coordinate_x, int move_coordinate_y, int current_player)
{
    update_board_array(board, EMPTY_SQUARE, piece_coordinate_x, piece_coordinate_y);
    update_board_array(board, character, move_coordinate_x, move_coordinate_y);
    clear_screen();
    draw_board(board, current_player);
}

int next_player(int current_player)
{
    return current_player = !current_player;
}

void colour_selected_piece(char board[][ROW_MAX + 1][MESSAGE], char code[], int current_player, int x, int y)
{
    char temp_string[ESCAPE_CODE];

    if (check_king(board, current_player, x, y))
    {
        strcpy(temp_string, current_player ? "B" : "W");
    }
    else
    {
        strcpy(temp_string, current_player ? "b" : "w");
    }

    if (strlen(code) > strlen(CLEAR_COLOUR))
    {
        strcat(temp_string, CLEAR_COLOUR);
        strcat(code, temp_string);
        strcpy(temp_string, code);
    }
    update_board_array(board, temp_string, x, y);
    clear_screen();
    draw_board(board, current_player);
}
bool take_piece(char board[][ROW_MAX + 1][MESSAGE], bool is_king, int piece_coordinate_x, int piece_coordinate_y,
                                                    int move_coordinate_x, int move_coordinate_y, int current_player)
{
    int entered_x_coordinate, entered_y_coordinate, x_coordinate, y_coordinate, temp_x, temp_y;
    int multiplyer_x, multiplyer_y = current_player ? -1 : 1;
    int piece_to_take = current_player ? PLAYER_WHITE : PLAYER_BLACK;
    char temp_board[COLUMN_MAX + 1][ROW_MAX + 1][MESSAGE];
    char *p_player_letter = is_king ? current_player ? "B" : "W" : current_player ? "b" : "w";

    for (y_coordinate = ROW_MIN; y_coordinate <= ROW_MAX; y_coordinate++)
    {
        for (x_coordinate = COLUMN_MIN; x_coordinate <= COLUMN_MAX; x_coordinate++)
        {
            strcpy(temp_board[x_coordinate][y_coordinate], board[x_coordinate][y_coordinate]);
        }
    }
    temp_x = piece_coordinate_x;
    temp_y = piece_coordinate_y;
    while (1)
    {
        printf("enter the x co-ordinate of the piece you wish to take: ");
        scanf(" %1d", &entered_x_coordinate);
        printf("enter the y co-ordinate of the piece you wish to take: ");
        scanf(" %1d", &entered_y_coordinate);
        multiplyer_x = entered_x_coordinate - temp_x;
        if (is_king && entered_y_coordinate - temp_y == -1)
        {
            multiplyer_y = current_player ? 1 :-1;
        }
        else
        {
            multiplyer_y = current_player ? -1 : 1;
        }
        if ((entered_x_coordinate - temp_x == 1 * multiplyer_x)  && (entered_y_coordinate - temp_y == 1 * multiplyer_y))
        {
            if (validate_piece(temp_board, piece_to_take, entered_x_coordinate, entered_y_coordinate))
            {
                if (off_board((temp_x + 2 * multiplyer_x), (temp_y + 2 * multiplyer_y)) == false)
                {
                    if (valid_square(temp_board, temp_x + 2 * multiplyer_x, temp_y + 2 * multiplyer_y))
                    {
                        strcpy(temp_board[temp_x + 1 * multiplyer_x][temp_y + 1 * multiplyer_y], TAKEN_PIECE);
                        temp_x += 2 * multiplyer_x;
                        temp_y += 2 * multiplyer_y;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
        if (temp_x == move_coordinate_x && temp_y == move_coordinate_y)
        {
            break;
        }
    }

    if (temp_x == move_coordinate_x && temp_y == move_coordinate_y)
    {
        for (y_coordinate = ROW_MAX; y_coordinate >= ROW_MIN; y_coordinate--)
        {
            for (x_coordinate = COLUMN_MIN; x_coordinate <= COLUMN_MAX; x_coordinate++)
            {
                if (strcmp(temp_board[x_coordinate][y_coordinate], TAKEN_PIECE) == 0)
                {
                    update_board_array(board, EMPTY_SQUARE, x_coordinate, y_coordinate);
                }
            }
        }
        update_board_array(board, EMPTY_SQUARE, piece_coordinate_x, piece_coordinate_y);
        update_board_array(board, p_player_letter, move_coordinate_x, move_coordinate_y);
        return true;
    }

    return false;
}
void count_pieces(char board[][ROW_MAX + 1][MESSAGE], int *p_number_of_white_pieces, int *p_number_of_black_pieces)
{
    int x_coordinate, y_coordinate;
    *p_number_of_white_pieces = 0;
    *p_number_of_black_pieces = 0;

    for (y_coordinate = ROW_MIN; y_coordinate <= ROW_MAX; y_coordinate++)
    {
        for (x_coordinate = COLUMN_MIN; x_coordinate <= COLUMN_MAX; x_coordinate++)
        {
            if (strcmp(board[x_coordinate][y_coordinate], "w") == 0 || (strcmp(board[x_coordinate][y_coordinate], "W")) == 0)
            {
                *p_number_of_white_pieces += 1;
            }
            if (strcmp(board[x_coordinate][y_coordinate], "b") == 0 || strcmp(board[x_coordinate][y_coordinate], "B") == 0)
            {
                *p_number_of_black_pieces += 1;
            }
        }
    }
    printf("there are %d white pieces left and %d black pieces left\n", *p_number_of_white_pieces, *p_number_of_black_pieces);
}

void move_test(char board[][ROW_MAX + 1][MESSAGE])
{

    int x_coordinate, y_coordinate;
    char piece_colour[MESSAGE];


    for (y_coordinate = ROW_MIN; y_coordinate <= ROW_MAX; y_coordinate++)
    {
        for (x_coordinate = COLUMN_MIN; x_coordinate <= COLUMN_MAX; x_coordinate++)
        {
            strcpy(piece_colour, " ");
            update_board_array(board, piece_colour, x_coordinate, y_coordinate);
        }
    }
    draw_board(board, PLAYER_BLACK);
    update_board_array(board, "b", 1, 1);
    update_board_array(board, "b", 3, 1);
    update_board_array(board, "w", 2, 0);
    update_board_array(board, "b", 3, 3);
    update_board_array(board, "b", 5, 3);
    update_board_array(board, "b", 1, 5);
    update_board_array(board, "b", 3, 5);
    draw_board(board, PLAYER_WHITE);
}

void game_over(int current_player)
{
    char winner[] = "Black Wins";

    strcpy(winner, current_player ? "Black Wins" : "White Wins");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t %s\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", winner);
    exit(0);
}
