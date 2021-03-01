/* board.h */
#ifndef _BOARD_
#define _BOARD_
using namespace std;
#include "tetrimino.h"
#include "window_surface.h"
//#include <SDL/SDL_ttf.h>

/**
 * FREE : grill case empty, FILLED : grill case filled 
 * **/

/***
 *score:
  -ligne : 40 points 
  -deux lignes  :100 points
  -trois lignes : 300 points
  -quatre lignes : 1200 points .
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
    MOV_DIRECTION direction;
    SDL_Color *color[8];
    int totalLines;
    unsigned long totalScore;
    //TTF_Font *font;

public:
    vector<vector<int>> screenWithBlock;  // the screen with the falling block
    vector<vector<int>> screenBackground; // the screen without the falling block
    Board();

    void setCurrentPiece(Tetrimino *tetr);
    Tetrimino *getCurrentPiece();
    void print_board();
    void draw_board(SDL_Renderer *rend);
    void print_piece_to_board();
    void print_piece_to_background();
    void refresh_screen();
    int DetectCollision();
    int LookDown(int idy, int idx);
    int LookRight(int idy, int idx);
    int LookLeft(int idy, int idx);
    int TryRotate();
    bool IsGameOver();
    void GoFarDown();
    void LineFull();
    void BringDownColumns(int i_row);
    void update_direction(MOV_DIRECTION direction_);
    void moveCurrentPiece();
    void moveBackCurrentPiece();
    tetrimino_type GetRandomShape();
    Tetrimino* GenerateRandomShape();
};

#endif