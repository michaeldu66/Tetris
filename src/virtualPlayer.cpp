#include "virtualPlayer.h"
#include "board.h"

/*virtualPlayer::virtualPlayer(Board *board) : b(board)
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

// Check la meilleure orientation et 
// renvoie le nb de fois qu'il faut
// appeler la fonction UP sur la piece 
// pour l'orientation

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
}*/

virtualPlayer::virtualPlayer(Board *board) : b(board)
{
    direction = NO_MOVE;
    /*pos = (posTetr*)malloc(sizeof(posTetr)); // cast explicite sur malloc car cpp fait des siennes en compilant avec g++
    //posTetr pos[sizeof(posTetr)];
    pos->best_pos_tetr_x = 0;
    pos->best_pos_tetr_y = 0;
    pos->score = 0;
    pos->best_numrot = 0;
    pos->nbTrouMin = 19;*/
    int best_pos_tetr_x = 0;
    int best_plusbas = -1;
    int best_numrot = 0;
    int nbTrouMin = 19;
    int best_score = 0;
    bool IsFirst = true;
    bool IsHold = false;
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

int virtualPlayer::NbTrou()
{
    int nbtrou = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (b->currentPiece->current_tetr[i][j])
            {
                int ind_i = i;
                while (b->LookDown(ind_i, j) == 0)
                {
                    nbtrou += 1;
                    ind_i++;
                }
            }
        }
    }
    return nbtrou;
}

int virtualPlayer::PlusBas()
{
    int plusbas = -1;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (b->currentPiece->current_tetr[i][j] != 0 && b->currentPiece->y - ORIGIN_Y + i > plusbas)
            {
                plusbas = b->currentPiece->y - ORIGIN_Y + i;
            }
        }
    }
    return plusbas;
}

void virtualPlayer::checkBestPosition(bool IsPieceHold)
{
    int nbTrou = 0;
    int plusbas = 0;
    int score = 0;
    int ind_x = 0;

    //int y_ini = b->currentPiece->y;

    sliceFarLeft();

    b->GoFarDown();
    b->print_piece_to_background();

    nbTrou = NbTrou();
    plusbas = PlusBas();

    /*if (plusbas > best_pos_tetr_y)
    {
        nbTrouMin = nbTrou;
        best_numrot = b->currentPiece->get_num_rot();
        best_pos_tetr_x = ind_x;
        best_pos_tetr_y = plusbas;
        IsHold = IsPieceHold;
    }

    else if (plusbas == best_pos_tetr_y && nbTrou < nbTrouMin)
    {
        nbTrouMin = nbTrou;
        best_numrot = b->currentPiece->get_num_rot();
        best_pos_tetr_x = ind_x;
        IsHold = IsPieceHold;
    }*/

    
    score = b->totalScore + b->computeScore(b->nbLineFull());
    if (score > best_score)
    {
        best_score = score;
        nbTrouMin = nbTrou;
        best_numrot = b->currentPiece->get_num_rot();
        best_pos_tetr_x = ind_x;
        best_plusbas = plusbas;
        IsHold = IsPieceHold;
    }

    else if (score == best_score && plusbas > best_plusbas)
    {
        nbTrouMin = nbTrou;
        best_numrot = b->currentPiece->get_num_rot();
        best_pos_tetr_x = ind_x;
        best_plusbas = plusbas;
        IsHold = IsPieceHold;
    }

    else if (score == best_score && plusbas == best_plusbas && nbTrou < nbTrouMin)
    {
        nbTrouMin = nbTrou;
        best_numrot = b->currentPiece->get_num_rot();
        best_pos_tetr_x = ind_x;
        IsHold = IsPieceHold;
    }

    b->deletePieceFromBackground();
    b->currentPiece->set_coord(b->currentPiece->x, 3);
    //b->GoFarUp();

    b->update_direction(RIGHT);

    while (!b->DetectCollision()) // detection quand on touche le coté de droite
    {
        b->moveCurrentPiece();
        ind_x++;
        b->GoFarDown();
        b->print_piece_to_background();

        nbTrou = NbTrou();
        plusbas = PlusBas();

        score = b->totalScore + b->computeScore(b->nbLineFull());
        if (score > best_score)
        {
            best_score = score;
            nbTrouMin = nbTrou;
            best_numrot = b->currentPiece->get_num_rot();
            best_pos_tetr_x = ind_x;
            best_plusbas = plusbas;
            IsHold = IsPieceHold;
        }

        else if (score == best_score && nbTrou < nbTrouMin)
        {
            nbTrouMin = nbTrou;
            best_numrot = b->currentPiece->get_num_rot();
            best_pos_tetr_x = ind_x;
            best_plusbas = plusbas;
            IsHold = IsPieceHold;
        }

        else if (score == best_score && nbTrou == nbTrouMin && plusbas > best_plusbas)
        {
            best_numrot = b->currentPiece->get_num_rot();
            best_pos_tetr_x = ind_x;
            best_plusbas = plusbas;
            IsHold = IsPieceHold;
        }
        /*if (score > pos->score)
        {
            pos->score = score;
            pos->nbTrouMin = nbTrou;
            pos->best_numrot = b->currentPiece->get_num_rot();
            pos->best_pos_tetr_x = ind_x;
            pos->best_pos_tetr_y = plusbas;
        }

        else if (score == pos->score && nbTrou < pos->nbTrouMin)
        {
            pos->nbTrouMin = nbTrou;
            pos->best_numrot = b->currentPiece->get_num_rot();
            pos->best_pos_tetr_x = ind_x;
            pos->best_pos_tetr_y = plusbas;
        }

        else if (score == pos->score && nbTrou == pos->nbTrouMin && plusbas > pos->best_pos_tetr_y)
        {
            pos->best_numrot = b->currentPiece->get_num_rot();
            pos->best_pos_tetr_x = ind_x;
            pos->best_pos_tetr_y = plusbas;
        }*/
        /*if (plusbas > best_pos_tetr_y)
        {
            nbTrouMin = nbTrou;
            best_numrot = b->currentPiece->get_num_rot();
            best_pos_tetr_x = ind_x;
            best_pos_tetr_y = plusbas;
            IsHold = IsPieceHold;
        }

        else if (plusbas == best_pos_tetr_y && nbTrou < nbTrouMin)
        {
            nbTrouMin = nbTrou;
            best_numrot = b->currentPiece->get_num_rot();
            best_pos_tetr_x = ind_x;        
            IsHold = IsPieceHold;
        }*/

        b->deletePieceFromBackground();
        //b->GoFarUp();
        b->currentPiece->set_coord(b->currentPiece->x, 3);
        b->update_direction(RIGHT);
    }
    return;
}

void virtualPlayer::chkAllCombinaison()
{
    bool IsPieceHold = false;

    if (IsFirst == true) // si c'est la première pièce, on la hold tout de suite
    {
        b->changePiece();
        IsFirst == false;
        return;
    }
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            checkBestPosition(IsPieceHold);
            b->update_direction(ROT_R);
            b->moveCurrentPiece();
           // b->currentPiece->rotate(ROT_R);
        }
        b->changePiece();    
        IsPieceHold = !IsPieceHold;
    }

    if (IsHold == false)
    {
        b->set_nbHold(0);
        b->changePiece();
    }

    IsHold = false;

    nbTrouMin = 19;
    best_plusbas = -1;

    while (b->currentPiece->get_num_rot() != best_numrot)
    {
        //b->currentPiece->rotate(ROT_R);
        b->update_direction(ROT_R);
        b->moveCurrentPiece();
    }

    sliceFarLeft();
    b->update_direction(RIGHT);
    for (int j = 0; j < best_pos_tetr_x; j++)
    {
        b->moveCurrentPiece();
    }

    //SDL_Delay(1000 / (1 + (b->get_level() + 1) / 15));

    b->GoFarDown();
    b->set_IsOut(false);
    b->currentPiece->set_finished();
    b->update_direction(NO_MOVE);

    //b->print_piece_to_board();

    return;
}