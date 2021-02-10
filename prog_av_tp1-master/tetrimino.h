#ifndef _TETRIMINO_
#define _TETRIMINO_
using namespace std;
#include <iostream>
#include <SDL.h>

bool matrix[7][4][4] = {
    {{1, 1, 1, 1},
     {0, 0, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},

    {{1, 1, 0, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},

    {{0, 1, 0, 0},
     {1, 1, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},

    {{0, 0, 1, 0},
     {1, 1, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},

    {{1, 0, 0, 0},
     {1, 1, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},

    {{1, 1, 0, 0},
     {0, 1, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},

    {{0, 1, 1, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}};

typedef enum tetrimino_type
{
    BARRE,
    BLOC,
    T_TYPE,
    L_TYPE,
    L_REVERSE,
    Z_TYPE,
    S_TYPE
} tetrimino_type;

typedef enum color_type
{
    RED,
    GREEN,
    BLUE
} color_type;

class Tetrimino
{
protected:
    SDL_Color *color;
    tetrimino_type type_t;
    color_type color_t;
    double x, y;
    int size;

public:
    Tetrimino(double x_, double y_, int size_, tetrimino_type type_t_, color_type color_t_);
    void print_tetrimino();
};

#endif