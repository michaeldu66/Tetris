/* board.h */
#ifndef _BOARD_
#define _BOARD_
using namespace std;
#include "tetrimino.h"
#include "window_surface.h"
#include <SDL2/SDL_ttf.h>
#include "SDL2/SDL_mixer.h"

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

typedef enum optionInfo
{
    SCORE,
    //LINES,
    LEVEL,
} optionInfo;

const int BOARD_HEIGHT = 20;
const int BOARD_WIDTH = 10;

const int ORIGIN_X = 11;
const int ORIGIN_Y = 6;

class Board
{
private:
    static vector<vector<vector<int>>> tetr_wallkick_barre;
    static vector<vector<vector<int>>> tetr_wallkick_reste;

    SDL_Rect *carre_grill;
    SDL_Color *color[8];
    int nbHold; // Nombre de fois qu'on a utilisé le hold par pièce (une seule fois autorisée par pièce)
    int totalLines;
    int Level;
    bool IsOut;


    /* display on the screen infos */
    TTF_Font *police;
    SDL_Color colorPolice;
    SDL_Surface *textSurface;
    SDL_Rect *positionInfos;

    SDL_Texture *textTexture;
    char infosMsg[100];

public:
    Tetrimino * currentPiece; // La pièce courante se trouvant sur l'aire de jeu
    Tetrimino * holdPiece; // La pièce qui est gardée via la touche C
    Tetrimino * NextPieces[3]; // Les 3 prochaines pièces
    MOV_DIRECTION direction;
    vector<vector<int>> screenWithBlock;  // the screen with the falling block
    vector<vector<int>> screenBackground; // the screen without the falling block
    vector<vector<int>> screenHold; // the screen with the hold piece
    vector<vector<int>> screenNextPieces; // the screen with the 3 next pieces
    //vector<vector<int>> screenIABackground; // screenBackground to try the possibilities for the ia
    int totalScore;
    Board();

    void setCurrentPiece(Tetrimino *tetr);
    Tetrimino *getCurrentPiece();
    void print_board();
    void draw_board(SDL_Renderer *rend);
    void print_piece_to_board();
    void deletePieceFromBackground();
    void print_piece_to_background();
    void print_piece_to_hold();
    void print_piece_to_next();
    void print_projection();
    void update_screenNextPieces();
    void refresh_screen();
    int DetectCollision();
    int LookDown(int idy, int idx);
    int LookUp(int idy, int idx);
    int LookRight(int idy, int idx);
    int LookLeft(int idy, int idx);
    void TryRotate();
    //bool IsGameOver();
    void GoFarDown();
    void GoFarUp();
    int LineFull();
    void BringDownColumns(int i_row);
    int nbLineFull();
    void UpdateLevel();
    int get_level();
    void set_nbHold(int new_nbHold);
    int get_nbHold();
    bool get_IsOut();
    void update_direction(MOV_DIRECTION direction_);
    void moveCurrentPiece();
    //void moveBackCurrentPiece();
    void changePiece();
    tetrimino_type GetRandomShape();
    Tetrimino * GenerateRandomShape();

    int computeScore(int nbLines);
    void setScore(int valueToAdd);

    int get_score();
    void setPositionInfos(optionInfo infos);
    void textInfos(optionInfo infos);
    void printInfosToScreen(SDL_Renderer *rend);
    void freeScoreText();
};

#endif