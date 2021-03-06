#include "virtualPlayer.h"

virtualPlayer::virtualPlayer(Board *board) : b(board)
{
    direction = NO_MOVE;
    pos = (posTetr *)malloc(sizeof(posTetr)); // cast explicite sur malloc car cpp fait des siennes en compilant avec g++
    pos->x = 0;
    pos->nbUp = 0;
    pos->value = 0;
};

bool virtualPlayer::sliceToLeft()
{
    //direction = LEFT;
    while (!b->IsGameOver())
    {
        b->update_direction(LEFT);
        while (!b->DetectCollision())
        {
            b->moveCurrentPiece();
        }

        b->GoFarDown();
        b->print_piece_to_board();

        if (b->getCurrentPiece()->getStateFinished())
        {
            b->print_piece_to_background(); // print la pièce dans le background avant de générer la suivante
            b->LineFull();                  //Efface les lignes pleines
            b->setCurrentPiece(b->GenerateRandomShape());
        }
    }
    return true;
}
