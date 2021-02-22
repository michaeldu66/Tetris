/* board.h */
#ifndef _BOARD_
#define _BOARD_
using namespace std;
#include "tetrimino.h"
#include "window_surface.h"

/**
 * FREE : grill case empty, FILLED : grill case filled 
 * **/

enum
{
    FREE,
    FILLED
};

const int BOARD_HEIGHT = 20;
const int BOARD_WIDTH = 10;

const int ORIGIN_X = 11;
const int ORIGIN_Y = 6;

class Board
{
private:
    Tetrimino *currentPiece; // La pièce courante se trouvant sur l'aire de jeu
    SDL_Rect *carre_grill;

public:
    vector<vector<int>> area; // Le tableau représentant l'aire de jeu
    //double area[20][10];
    Board(Tetrimino* piece);

    void setCurrentPiece(Tetrimino *tetr);
    Tetrimino *getCurrentPiece();
    void print_board();
    void draw_board(SDL_Renderer *rend);
    void print_piece_to_board();
};

#endif