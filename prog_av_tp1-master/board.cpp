#include "board.h"
/* board.cpp */
Board::Board(Tetrimino* tetr_origin)
{
    carre_grill = new SDL_Rect();
    carre_grill->h = TETR_SIZE;
    carre_grill->w = TETR_SIZE;

    area.resize(BOARD_HEIGHT); // Allocation des vectors
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        area[i].resize(BOARD_WIDTH);
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            area[i][j] = FREE;
        }
    }
    currentPiece = tetr_origin;
    cout << "BOARD constructor" << endl;
}

void Board::setCurrentPiece(Tetrimino *tetr)
{
    currentPiece = tetr;
}

Tetrimino *Board::getCurrentPiece()
{
    return currentPiece;
}

void Board::print_board()
{
    cout << "affichage du board"<< endl;
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            cout << area[i][j];
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Board::draw_board(SDL_Renderer *rend)
{
    print_board();
    for (int i = 0; i < BOARD_HEIGHT; i ++) //centrée en hauteur
    {
        for (int j = 0; j < BOARD_WIDTH; j ++)
        {
            carre_grill->x = (ORIGIN_X + j)*TETR_SIZE;
            carre_grill->y = (ORIGIN_Y + i)*TETR_SIZE;
            SDL_SetRenderDrawColor(rend, 150, 150, 150, 255); // inside of squares black
            SDL_RenderFillRect(rend, carre_grill);
            SDL_SetRenderDrawColor(rend, 75, 75, 75, 0);
            SDL_RenderDrawRect(rend, carre_grill); //borderline of squares (in white)
        }
    }
}

void Board::print_piece_to_board()
{
    for(int i=0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++){
            area[currentPiece->y-ORIGIN_Y+i][currentPiece->x-ORIGIN_X+j] = currentPiece->current_tetr[i][j];
        }
    }

}