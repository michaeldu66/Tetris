#include "virtualPlayer.h"

virtualPlayer::virtualPlayer(Board *board) : b(board)
{
    direction = NO_MOVE;
    pos = (posTetr *)malloc(sizeof(posTetr)); // cast explicite sur malloc car cpp fait des siennes en compilant avec g++
    pos->x = 0;
    pos->nbUp = 0;
    pos->value = 0;
};

void virtualPlayer::sliceToLeft()
{
    //direction = LEFT;
    b->update_direction(LEFT);
    while (!b->DetectCollision())
    {
        b->moveCurrentPiece();
    }

    b->GoFarDown();
    b->print_piece_to_board();

    return;
}
