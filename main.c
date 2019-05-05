#include "board.h"

bool check_king(char board[][ROW_MAX + 1], int x_coordinate, int y_coordinate);
bool calculate_move(char board[][ROW_MAX +1], int current_player, int piece_coordinate_x,
                    int piece_coordinate_y, int move_coordinate_x, int move_coordinate_y);
void move_1_square(char board[][ROW_MAX +1], char character, int piece_coordinate_x,
                    int piece_coordinate_y, int move_coordinate_x, int move_coordinate_y, int current_player);
int main()
{
    enum player current_player = PLAYER_WHITE;
    char board[COLUMN_MAX + 1][ROW_MAX + 1];
    int x_coordinate_of_piece, y_coordinate_of_piece, x_coordinate_to_move_to, y_coordinate_to_move_to;

    current_player = initalize_game(board, current_player);
    clear_screen();
    draw_board(board, current_player);
    while (1)
    {
        get_coordinates(board, false, current_player, &x_coordinate_of_piece, &y_coordinate_of_piece);
        if (off_board(x_coordinate_of_piece, y_coordinate_of_piece) == false)
        {
            if (validate_piece(board, current_player, x_coordinate_of_piece, y_coordinate_of_piece) == true)
            {
                get_coordinates(board, true, current_player, &x_coordinate_to_move_to, &y_coordinate_to_move_to);
                if (off_board(x_coordinate_to_move_to, y_coordinate_to_move_to) == false)
                {
                    if (valid_square(board, x_coordinate_to_move_to, y_coordinate_to_move_to) == true)
                    {
                        if (check_king(board, x_coordinate_of_piece, y_coordinate_of_piece) == true)
                        {
                            break;
                        }
                        else
                        {
                            if (calculate_move(board, current_player, x_coordinate_of_piece, y_coordinate_of_piece,
                                               x_coordinate_to_move_to, y_coordinate_to_move_to) == true)
                            {
                                break;
                            }
                            else
                            printf("invalid move\n");
                        }
                    }
                    else
                    {
                        printf("invalid square");
                        break;
                    }
                }
                else
                {
                    printf("new co-ordinates are off the board\n");
                }
            }
            else
            {
                printf("no piece of your colour at %d,%d\n", x_coordinate_of_piece, y_coordinate_of_piece);
            }
        }
        else
        {
            printf("co-ordinates are off the board\n");
        }
    }

    return 0;
}

bool check_king(char board[][ROW_MAX + 1], int x_coordinate, int y_coordinate)
{
    return ((board[x_coordinate][y_coordinate] == 'W') || (board[x_coordinate][y_coordinate] == 'B')) ? true : false;
}

bool calculate_move(char board[][ROW_MAX +1], int current_player, int piece_coordinate_x,
                    int piece_coordinate_y, int move_coordinate_x, int move_coordinate_y)
{
    if (move_coordinate_y - piece_coordinate_y < 0)
    {
        return false;
    }
    else if ((move_coordinate_y - piece_coordinate_y == 1) && ((move_coordinate_x - piece_coordinate_x == -1) ||
            (move_coordinate_x - piece_coordinate_x == 1)))
    {
        current_player ? move_1_square(board,'b', piece_coordinate_x, piece_coordinate_y, move_coordinate_x,
                                       move_coordinate_y, current_player) : move_1_square(board, 'w',piece_coordinate_x,
                                       piece_coordinate_y, move_coordinate_x, move_coordinate_y, current_player);
        return true;
    }
    else
    {
        // call piece take piece
        return true;
    }
}

void move_1_square(char board[][ROW_MAX +1], char character, int piece_coordinate_x,int piece_coordinate_y, int move_coordinate_x, int move_coordinate_y, int current_player)
{
    update_board_array(board, ' ', piece_coordinate_x, piece_coordinate_y);
    update_board_array(board, character, move_coordinate_x, move_coordinate_y);
    clear_screen();
    draw_board(board, current_player);
}
