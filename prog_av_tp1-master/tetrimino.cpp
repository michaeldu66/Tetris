#include "tetrimino.h"
Tetrimino::Tetrimino(double _x, double _y, int _size, tetrimino_type _type_t, color_type _color_t)
    : x(_x), y(_y), size(_size), type_t(_type_t), color_t(_color_t)
{
    bool blabla[4][4] = {matrix[type_t]};
};