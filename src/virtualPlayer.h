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
    Board* b;
    MOV_DIRECTION direction; //la direction que choisit l'IA
    //posTetr* pos;
    int best_pos_tetr_x;
    int best_pos_tetr_y;
    int best_numrot;
    int nbTrouMin;
    int best_score;
    bool IsFirst;
    bool IsHold;

public:
    virtualPlayer(Board* board);
    void sliceFarLeft();
    //void checkBestOrientation(int cptSlideRight);
    void checkBestOrientation(bool IsPieceHold);
    void chkAllCombinaison();
    int NbTrou();
    int PlusBas();
};

#endif