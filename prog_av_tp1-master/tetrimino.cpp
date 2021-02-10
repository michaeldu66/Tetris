#include "tetrimino.h"
Tetrimino::Tetrimino(double x_, double y_, int size_, tetrimino_type type_t_, color_type color_t_)
    : x(x_), y(y_), size(size_), type_t(type_t_), color_t(color_t_)
{
    color = new SDL_Color();
    switch(color_t){
        case RED:
        color->r = 255;
        color->g = 0;
        color->b = 0;
        break;

        case GREEN:
        color->r = 0;
        color->g = 255;
        color->b = 0;
        break;

        case BLUE:
        color->r = 0;
        color->g = 0;
        color->b = 255;
        break;
    }
    cout << "test"<<endl;
};


void Tetrimino::print_tetrimino()
{
    cout << "affichage du tetrimino  " << type_t<<endl;
    for(int i = 0; i< 4; i++){
        for(int j = 0; j<4; j++){
            cout << matrix[type_t][i][j] + " ";
        }
        cout << endl;
    }
}



bool Tetrimino::matrix[7][4][4] = {
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