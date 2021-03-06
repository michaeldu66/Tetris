/* board.h */
#ifndef _VIRTUAlPLAYER_
#define _VIRTUAlPLAYER_
using namespace std;
#include "board.h"

typedef struct posTetr
{
    int x;
    int nbUp;
    int value;
} posTetr;

class VirtualPlayer
{
protected:
    Board *b;
    MOV_DIRECTION direction; //la direction que choisit l'IA
    posTetr* pos;


public:
    VirtualPlayer(Board *board_);
    void dropLowestPossible();
};

#endif