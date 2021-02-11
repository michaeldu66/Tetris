#include "tetrimino.h"

int Tetrimino::matrix[7][4][4] = {
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

Tetrimino::Tetrimino(double x_, double y_, int size_, tetrimino_type type_t_, color_type color_t_)
    : x(x_), y(y_), size(size_), type_t(type_t_), color_t(color_t_)
{
    color = new SDL_Color();
    shape = new SDL_Rect();
    shape->h = TILE_SIZE;
    shape->w = TILE_SIZE;
    switch (color_t)
    {
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
    cout << "Tetrimino constructor" << endl;
};

// Just to check if te matrix of the tetrimino is ok in the terminal
void Tetrimino::print_tetrimino()
{
    cout << "affichage du tetrimino  " << type_t << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << matrix[type_t][i][j];
            cout << " ";
        }
        cout << endl;
    }
}

void Tetrimino::draw(SDL_Renderer *rend)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (matrix[type_t][i][j])
            {
                shape->x = (x + j) * TILE_SIZE;   // coord of squares
                shape->y = (y + i) * TILE_SIZE;   // caution! ==> x for columns and y for lines
                SDL_SetRenderDrawColor(rend, color->r, color->g, color->b, 255); // inside of squares
                SDL_RenderFillRect(rend, shape);
                SDL_SetRenderDrawColor(rend, 219, 219, 219, 255);
                SDL_RenderDrawRect(rend, shape); //borderline of squares (in white)
            }
        }
    }
}