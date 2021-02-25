#include "board.h"
Board::Board()
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

    currentPiece = GenerateRandomShape();
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
    cout << "direction set to " << direction << endl;
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
    case NO_MOVE:
        cout << "on bouge pas la piece" << endl;
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
    //print_board();
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
                if (OutOfGrillLeft(currentPiece->x, j) ||
                    OutOfGrillRight(currentPiece->x, j))
                {
                    cout << "Detection Side Detected" << endl;
                    moveBackCurrentPiece();
                    return 1;
                }
                else if (OutOfGrillDown(currentPiece->y, i))
                {
                    cout << "Detection Down Detected" << endl;
                    cout << " le state est "<< currentPiece->getStateFinished() << endl;
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
    cout << "coord : " << coord << ", ORIGIN_Y : " << ORIGIN_Y << endl;
    int val = coord - ORIGIN_Y + idx + 1;
    cout << "le tout : " << val << endl;
    if (coord - ORIGIN_Y + idx + 1 > 20)
    {
        currentPiece->set_finished();
        cout << "Current Piece set to finished" << endl;
        return 1;
    }
    return 0;
}

int Board::OutOfGrillRight(int coord, int idx)
{
    return (coord - ORIGIN_X + idx + 1 > 10) ? 1 : 0;
}

int Board::OutOfGrillLeft(int coord, int idx)
{
    return (coord - ORIGIN_X + idx < 0) ? 1 : 0;
}

color_type Board::GetRandomColor()
{
    srand(time(NULL));
    int Color = rand() % 3;
    cout << "the random color is : " << Color << endl;
    switch (Color)
    {
    case 0:
        return BLUE;
    case 1:
        return RED;
    case 2:
        return GREEN;
    }
    return BLUE;
}

tetrimino_type Board::GetRandomShape()
{
    srand(time(NULL));
    int Shape = rand() % 7;
    cout << "the random Shape is : " << Shape << endl;
    switch (Shape)
    {
    case 0:
        return BARRE;
    case 1:
        return BLOC;
    case 2:
        return T_TYPE;
    case 3:
        return L_TYPE;
    case 4:
        return L_REVERSE;
    case 5:
        return Z_TYPE;
    case 6:
        return S_TYPE;
    }
    return BARRE;
}

Tetrimino *Board::GenerateRandomShape()
{
    Tetrimino *randomTetrimino;
    tetrimino_type randomShape = GetRandomShape();
    color_type randomColor = GetRandomColor();
    if (randomShape == BARRE)
        randomTetrimino = new Tetrimino(14, 6, 4, randomShape, randomColor);
    else if (randomShape == BLOC)
        randomTetrimino = new Tetrimino(14, 6, 2, randomShape, randomColor);
    else
        randomTetrimino = new Tetrimino(14, 6, 3, randomShape, randomColor);
    currentPiece = randomTetrimino;
    cout << "New Random shape generated with coord : ";
    randomTetrimino->print_coord();
    return randomTetrimino;
}
