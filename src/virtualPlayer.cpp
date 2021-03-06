#include "virtualPlayer.h"




VirtualPlayer::VirtualPlayer(Board *board_):b(board_){
    direction = NO_MOVE;
    pos = (posTetr*)malloc(sizeof(posTetr)); // cast explicite sur malloc car cpp fait des siennes en compilant avec g++
    pos->x =0;
    pos->nbUp = 0;
    pos->value = 0;
};




