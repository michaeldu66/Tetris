/* board.h */
#ifndef _VIRTUAlPLAYER_
#define _VIRTUAlPLAYER_
using namespace std;
#include "board.h"



class VirtualPlayer
{
protected:
    Board* b;

public:
    VirtualPlayer(Board* board_);
};

#endif