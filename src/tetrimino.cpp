#include "tetrimino.h"

/* size sert à rien je crois*/


vector<vector<vector<vector<int>>>> Tetrimino::matrix2
{
    {
     {{0, 0, 0, 0},
     {1, 1, 1, 1},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},

     {{0, 0, 1, 0},
     {0, 0, 1, 0},
     {0, 0, 1, 0},
     {0, 0, 1, 0}},

     {{0, 0, 0, 0},
     {0, 0, 0, 0},
     {1, 1, 1, 1},
     {0, 0, 0, 0}},

     {{0, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 1, 0, 0}}
     },

    {
     {{0, 0, 0, 0},
     {0, 2, 2, 0},
     {0, 2, 2, 0},
     {0, 0, 0, 0}},

     {{0, 0, 0, 0},
     {0, 2, 2, 0},
     {0, 2, 2, 0},
     {0, 0, 0, 0}},

     {{0, 0, 0, 0},
     {0, 2, 2, 0},
     {0, 2, 2, 0},
     {0, 0, 0, 0}},

     {{0, 0, 0, 0},
     {0, 2, 2, 0},
     {0, 2, 2, 0},
     {0, 0, 0, 0}}
    },

    {
    {{0, 0, 0, 0},
     {0, 3, 0, 0},
     {3, 3, 3, 0},
     {0, 0, 0, 0}},

     {{0, 0, 0, 0},
     {0, 3, 0, 0},
     {0, 3, 3, 0},
     {0, 3, 0, 0}},

     {{0, 0, 0, 0},
     {0, 0, 0, 0},
     {3, 3, 3, 0},
     {0, 3, 0, 0}},

     {{0, 0, 0, 0},
     {0, 3, 0, 0},
     {3, 3, 0, 0},
     {0, 3, 0, 0}}
    },

    {
    {{0, 0, 0, 0},
     {0, 0, 4, 0},
     {4, 4, 4, 0},
     {0, 0, 0, 0}},

     {{0, 0, 0, 0},
     {0, 4, 0, 0},
     {0, 4, 0, 0},
     {0, 4, 4, 0}},

     {{0, 0, 0, 0},
     {0, 0, 0, 0},
     {4, 4, 4, 0},
     {4, 0, 0, 0}},

     {{0, 0, 0, 0},
     {4, 4, 0, 0},
     {0, 4, 0, 0},
     {0, 4, 0, 0}}
    },

    {
    {{0, 0, 0, 0},
     {5, 0, 0, 0},
     {5, 5, 5, 0},
     {0, 0, 0, 0}},

     {{0, 0, 0, 0},
     {0, 5, 5, 0},
     {0, 5, 0, 0},
     {0, 5, 0, 0}},

     {{0, 0, 0, 0},
     {0, 0, 0, 0},
     {5, 5, 5, 0},
     {0, 0, 5, 0}},

     {{0, 0, 0, 0},
     {0, 5, 0, 0},
     {0, 5, 0, 0},
     {5, 5, 0, 0}}
    },

    {
    {{0, 0, 0, 0},
     {6, 6, 0, 0},
     {0, 6, 6, 0},
     {0, 0, 0, 0}},

     {{0, 0, 0, 0},
     {0, 0, 6, 0},
     {0, 6, 6, 0},
     {0, 6, 0, 0}},

     {{0, 0, 0, 0},
     {0, 0, 0, 0},
     {6, 6, 0, 0},
     {0, 6, 6, 0}},

     {{0, 0, 0, 0},
     {0, 6, 0, 0},
     {6, 6, 0, 0},
     {6, 0, 0, 0}}
    },

    {
    {{0, 0, 0, 0},
     {0, 7, 7, 0},
     {7, 7, 0, 0},
     {0, 0, 0, 0}},

     {{0, 0, 0, 0},
     {0, 7, 0, 0},
     {0, 7, 7, 0},
     {0, 0, 7, 0}},

     {{0, 0, 0, 0},
     {0, 0, 0, 0},
     {0, 7, 7, 0},
     {7, 7, 0, 0}},

     {{0, 0, 0, 0},
     {7, 0, 0, 0},
     {7, 7, 0, 0},
     {0, 7, 0, 0}}
    }
};

vector<vector<vector<vector<int>>>> Tetrimino::tetr_wallkick
{
    {
    {{0, 1}, {0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}}, 
    {{0, 3}, {0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}},
    {{1, 2}, {0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}},
    {{1, 0}, {0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}}, 
    {{2, 3}, {0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}},
    {{2, 1}, {0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}}, 
    {{3, 0}, {0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}},
    {{3, 2}, {0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}}
    },

    {
    {{0, 1}, {0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},
    {{0, 3}, {0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},
    {{1, 2}, {0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},
    {{1, 0}, {0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},
    {{2, 3}, {0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},
    {{2, 1}, {0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},
    {{3, 0}, {0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, -2}},
    {{3, 2}, {0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, -2}}
    }
};

Tetrimino::Tetrimino(int x_, int y_, int size_, tetrimino_type type_t_)
    : x(x_), y(y_), size(size_), type_t(type_t_)
{
    num_rot = 0;
    color = new SDL_Color();
    shape = new SDL_Rect();
    shape->h = TETR_SIZE;
    shape->w = TETR_SIZE;
    switch (type_t_)
    {
    case BARRE:
        color->r = 0;
        color->g = 255;
        color->b = 255;
        break;

    case BLOC:
        color->r = 255;
        color->g = 255;
        color->b = 0;
        break;

    case T_TYPE:
        color->r = 255;
        color->g = 0;
        color->b = 255;
        break;

    case L_TYPE:
        color->r = 255;
        color->g = 128;
        color->b = 0;
        break;

    case Z_TYPE:
        color->r = 255;
        color->g = 0;
        color->b = 0;
        break;

    case S_TYPE:
        color->r = 0;
        color->g = 255;
        color->b = 0;
        break;

    case J_TYPE:
        color->r = 0;
        color->g = 0;
        color->b = 255;
        break;
    }

    current_tetr.resize(4); // Allocation des vectors
    for (int i = 0; i < 4; i++)
    {
        current_tetr[i].resize(4);
        for (int j = 0; j < 4; j++)
        {
            current_tetr[i][j] = matrix2[type_t][num_rot][i][j];
        }
    }
    finished = false;
    //print_tetrimino();
    //print_coord();
    cout << "Tetrimino constructor" << endl;
};

Tetrimino::~Tetrimino()
{
    current_tetr.clear();
    current_tetr.shrink_to_fit();
    delete color;
    delete shape;
    matrix2.clear();
    matrix2.shrink_to_fit();
    cout << "Tetrimino Destructor" << endl;
}


// Just to check if te matrix of the tetrimino is ok in the terminal
void Tetrimino::print_tetrimino()
{
    cout << "affichage du tetrimino  " << type_t << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << current_tetr[i][j];
            cout << " ";
        }
        cout << endl;
    }
}

/*void Tetrimino::transpose(void)
{
    vector<vector<int>> tmp;
    tmp.resize(4);
    for (int i = 0; i < size; i++)
    {
        tmp[i].resize(4);
        for (int j = 0; j < size; j++)
        {
            tmp[i][j] = current_tetr[i][j];
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            current_tetr[i][j] = tmp[j][i];
        }
    }
    tmp.clear();
    tmp.shrink_to_fit();
    return;
}*/

/*void Tetrimino::reverseCols(void)
{
    int tempval;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size / 2; j++)
        {
            tempval = current_tetr[i][j];
            current_tetr[i][j] = current_tetr[i][size - j - 1];
            current_tetr[i][size - j - 1] = tempval;
        }
    }
}*/

void Tetrimino::rotate(MOV_DIRECTION direction_)
{
    if (direction_ == ROT_R)
    {
        num_rot = (get_num_rot() + 1) % 4;
    }
    if (direction_ == ROT_L)
    {
        num_rot = (get_num_rot() + 3) % 4;
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            current_tetr[i][j] = matrix2[get_type()][num_rot][i][j];
        }
    }
    return;
}

void Tetrimino::set_coord(int x_, int y_)
{
    if (x_ != -1)
        x = x_;
    if (y_ != -1)
        y = y_;
}

tetrimino_type Tetrimino::get_type()
{
    return type_t;
}

int Tetrimino::get_num_rot()
{
    return num_rot;
}

vector<vector<vector<vector<int>>>> Tetrimino::get_wallkick()
{
    return tetr_wallkick;
}

void Tetrimino::print_coord()
{
    cout << "(" << x <<"," << y << ")" << endl;
}

void Tetrimino::set_finished()
{
    finished = true;
}

bool Tetrimino::getStateFinished()
{
    return finished;
}