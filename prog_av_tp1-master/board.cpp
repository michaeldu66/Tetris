#include "board.h"
/* board.cpp */
Board::Board(Tetrimino *tetr_origin)
{
    carre_grill = new SDL_Rect();
    carre_grill->h = TETR_SIZE;
    carre_grill->w = TETR_SIZE;

    screenWithBlock.resize(BOARD_HEIGHT);  // Allocation des vectors
    screenBackground.resize(BOARD_HEIGHT); // Allocation des vectors
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        screenBackground[i].resize(BOARD_WIDTH);
        screenWithBlock[i].resize(BOARD_WIDTH);
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            screenBackground[i][j] = FREE;
            screenWithBlock[i][j] = FREE;
        }
    }
    currentPiece = tetr_origin;
    direction = NO_MOVE;
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

void Board::update_direction(MOV_DIRECTION direction_)
{
    direction = direction_;
}

void Board::moveCurrentPiece()
{
    switch (direction)
    {
    case LEFT:
        currentPiece->x--;
        break;
    case RIGHT:
        currentPiece->x++;
        break;
    case DOWN:
        currentPiece->y++;
        break;
    case UP:
        currentPiece->rotate();
        break;
    }
}

void Board::moveBackCurrentPiece()
{
    switch (direction)
    {
    case LEFT:
        currentPiece->x++;
        break;
    case RIGHT:
        currentPiece->x--;
        break;
    case DOWN:
        currentPiece->y--;
        break;
    case UP:
        currentPiece->rotate();
        currentPiece->rotate();
        currentPiece->rotate();
        break;
    }
}

void Board::print_board()
{
    cout << "affichage du board" << endl;
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            cout << screenWithBlock[i][j];
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Board::draw_board(SDL_Renderer *rend)
{
    print_board();
    for (int i = 0; i < BOARD_HEIGHT; i++) //centrée en hauteur
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            carre_grill->x = (ORIGIN_X + j) * TETR_SIZE;
            carre_grill->y = (ORIGIN_Y + i) * TETR_SIZE;
            SDL_SetRenderDrawColor(rend, 150, 150, 150, 255); // inside of squares black
            SDL_RenderFillRect(rend, carre_grill);
            SDL_SetRenderDrawColor(rend, 75, 75, 75, 0);
            SDL_RenderDrawRect(rend, carre_grill); //borderline of squares (in white)
        }
    }
}

void Board::print_piece_to_board()
{
    refresh_screen();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (currentPiece->current_tetr[i][j])
                screenWithBlock[currentPiece->y - ORIGIN_Y + i][currentPiece->x - ORIGIN_X + j] = currentPiece->current_tetr[i][j];
        }
    }
}

void Board::refresh_screen()
{
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            if (screenBackground[i][j] != screenWithBlock[i][j])
                screenWithBlock[i][j] = screenBackground[i][j];
        }
    }
}

// // si les matrices de tetris sont full 0 on delete, fct à faire
// //quand piece bouge plus, on update le background

int Board::DetectCollision()
{
    moveCurrentPiece();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (currentPiece->current_tetr[i][j])
            {
                if (OutOfGrillDown(currentPiece->y, i) ||
                    OutOfGrillLeft(currentPiece->x, j) ||
                    OutOfGrillRight(currentPiece->x, j))
                {
                    cout << "Detection Detected" << endl;
                    moveBackCurrentPiece();
                    return 1;
                }
            }
        }
    }
    moveBackCurrentPiece();
    return 0;
}

int Board::OutOfGrillDown(int coord, int idx)
{
    return (coord - ORIGIN_Y + idx+1 > 20) ? 1 : 0;
}

int Board::OutOfGrillRight(int coord, int idx)
{
    return (coord - ORIGIN_X + idx+1 > 10) ? 1 : 0;
}

int Board::OutOfGrillLeft(int coord, int idx)
{
    return (coord - ORIGIN_X + idx < 0) ? 1 : 0;
}
