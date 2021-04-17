/* board.h */
#ifndef _VIRTUAlPLAYER_
#define _VIRTUAlPLAYER_
using namespace std;
#include "board.h"

// 	Tester toutes les positions tourner dans tous les sens et prendre la meilleur.
// La meilleur étant d'abord :
// 1) Celle qui fait le plus de ligne compléte
// 2) Si y en a pas, celle qui monte le moins haut et fait le moins de trou

/*typedef struct posTetr
{
    int x;
    int nbUp;
    int value;
} posTetr;

class virtualPlayer
{
protected:
    Board *b;
    MOV_DIRECTION direction; //la direction que choisit l'IA
    posTetr *pos;

public:
    virtualPlayer(Board *board);
    void sliceFarLeft();
    void checkBestOrientation(int cptSlideRight);
    void chkAllCombinaison();
};*/

typedef struct posTetr
{
    int best_pos_tetr_x;
    int best_pos_tetr_y;
    int best_numrot;
    int nbTrouMin;
    int score;
} posTetr;

class virtualPlayer
{
protected:

    /***
 * b : board of the IA_Player
 * direction : SERT A RIEN JE CROIS
 * pos : SERT A RIEN POUR L'INSTANT
 * best_pos_tetr_x : position x of the best piece
 * best_plusbas : position y of the lowest part of the best piece 
 * best_numrot : rotation number of the best position (of the best piece)
 * nbTrouMin : number of holes left by the best piece
 * best_score : score of the best piece
 * IsFirst : a bool stating if the piece we are testing is the first one or not 
 *              (if it is the first, it is put in the Hold)
 * IsHold : a bool stating if the piece we are testing is the Hold one or not
 * ***/
    Board* b;
    MOV_DIRECTION direction; 
    posTetr* pos;
    int best_pos_tetr_x;
    int best_plusbas;
    int best_numrot;
    int nbTrouMin;
    int best_score;
    bool IsFirst;
    bool IsHold;

public:

    /***
 * virtualPlayer constructor
 * ***/
    virtualPlayer(Board* board);

    /***
 * put the piece as far as possible on the left of the board (used to test all the position)
 * ***/
    void sliceFarLeft();

    /***
 * check all the position of the piece for one rotation state
 * the argument is to see if the piece we test is the one that is Hold or not
 * ***/
    void checkBestPosition(bool IsPieceHold);

    /***
 * check all the combinaison possible : call the checkBestPosition for each rotation state
 * and for both the Hold piece and the new one, then choose the best one and put it the
 * best position
 * ***/
    void chkAllCombinaison();

    /***
 * return the number of holes left by the piece we are testing
 * ***/
    int NbTrou();

    /***
 * return the lowest position y of the piece we are testing
 * ***/
    int PlusBas();
};

#endif