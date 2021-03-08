#include "virtualPlayer.h"
#include "board.h"

virtualPlayer::virtualPlayer(Board *board) : b(board)
{
    direction = NO_MOVE;
    pos = (posTetr *)malloc(sizeof(posTetr)); // cast explicite sur malloc car cpp fait des siennes en compilant avec g++
    pos->x = 0;
    pos->nbUp = 0;
    pos->value = 0;
};

void virtualPlayer::sliceFarLeft()
{
    b->update_direction(LEFT);
    while (!b->DetectCollision())
    {
        b->moveCurrentPiece();
    }
    return;
}
/*** Check la meilleure orientation et 
 * renvoie le nb de fois qu'il faut
 * appeler la fonction UP sur la piece 
 * pour l'orientation
 * ***/
int virtualPlayer::checkBestOrientation()
{
    int maxScore = 0;
    int score = 0;
    int idx = 0;
    MOV_DIRECTION dir = b->direction;

    b->update_direction(UP);
    for (int i = 0; i < 4; i++)
    {
        if(i)
            b->TryRotate();
        b->GoFarDown();
        b->print_piece_to_background();

        score = b->computeScore(b->nbLineFull());
        if (score > maxScore)
        {
            maxScore = score;
            idx = i;
        }

        b->deletePieceFromBackground();
        b->GoFarUp();
        b->print_piece_to_background();
    }
    b->TryRotate();//pour tourner 4 fois et revenir à la phase de depart
    b->direction = dir;
    return idx;
}

void virtualPlayer::chkAllCombinaison(){
    bool EndHorizontal = false;
    int cptSlideRight = 0;
    int idxMaxScorePosX=0,idxMaxScoreOrientation = 0;
    int score = 0, maxScore=0;
    b->update_direction(RIGHT);
    while (!b->DetectCollision())
    {
        b->moveCurrentPiece();
        cptSlideRight++;
        score = 
    }

}
