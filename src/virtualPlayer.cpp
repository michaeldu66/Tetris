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
void virtualPlayer::checkBestOrientation(int cptSlideRight)
{
    int score = 0;
    MOV_DIRECTION dir = b->direction;

    b->update_direction(ROT_R);
    for (int i = 0; i < 4; i++)
    {
        if (i)
        {
            b->moveCurrentPiece();
        }
        //b->deletePieceFromBackground(); //on a pas besoin de la print avant donc pas besoin de la supprimé
        b->GoFarDown();
        b->print_piece_to_background();
        //printf("avant de calculer le score\n");
        //b->print_board();

        score = b->totalScore + b->computeScore(b->nbLineFull());
        //printf("pour le tableau précédent, Score numero %i est egal à %i\n", i, score);
        if (score > pos->value)
        {
            //printf("eyaaaa");
            pos->value = score;
            pos->nbUp = i;
            pos->x = cptSlideRight;
        }

        b->deletePieceFromBackground();
        b->GoFarUp();
        //b->print_piece_to_background();
    }
    b->moveCurrentPiece(); //pour tourner 4 fois et revenir à la phase de depart
    b->direction = dir;
    //double monx = b->currentPiece->x - ORIGIN_X;
    //printf("pour ce x : %i, ce nbUp %i, on a la meilleure config a un score de %i\n", pos->x, pos->nbUp, pos->value);
    return;
}

void virtualPlayer::chkAllCombinaison()
{
    if (!b->currentPiece->getStateFinished())
    {
        MOV_DIRECTION dir = b->direction;
        bool EndHorizontal = false;
        int cptSlideRight = 0;
        int idxMaxScorePosX = 0, idxMaxScoreOrientation = 0;
        int score = 0, maxScore = 0;

        sliceFarLeft();
        b->update_direction(RIGHT);

        //On parcourt toutes les possibilités de gauche à droite
        checkBestOrientation(cptSlideRight);
        while (!b->DetectCollision()) // detection quand on touche le coté de droite
        {
            cptSlideRight++; //pour garder en memoire de cb on s'est déplacé
            b->moveCurrentPiece();
            checkBestOrientation(cptSlideRight);
        }

        //on repart de gauche et remet la pièce au score max
        sliceFarLeft();
        b->update_direction(RIGHT);
        for (int j = 0; j < pos->x; j++)
        {
            b->moveCurrentPiece();
        }

        b->update_direction(ROT_R);
        for (int j = 0; j < pos->nbUp; j++)
        {
            b->moveCurrentPiece();
        }

        b->update_direction(FAR_DOWN);
        b->moveCurrentPiece();
        b->currentPiece->set_finished();
        //printf("les valeurs max: \n");
        //printf("score : %i\n", pos->value);
        //printf("valeur x : %i\n", pos->x);
        //printf("nbUp : %i\n", pos->nbUp);
        //printf("fin de chkAllCombinaison\n");
        b->update_direction(NO_MOVE);
    }
    // sliceFarLeft();
    // b->update_direction(RIGHT);
    // for (int i = 0; i < cptSlideRight; i++)
    // {
    //     b->moveCurrentPiece();
    // }
    // b->direction = dir;
}
