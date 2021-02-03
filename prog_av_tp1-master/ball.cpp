#include "ball.h"

Ball::Ball(double _x, double _y, double _vx, double _vy) : x(_x), y(_y), vx(_vx), vy(_vy)
{
    this->(*srcBall) = {0, 96, 24, 24};
    cout << "ball créé" << endl;
};

double Ball::get_x()
{
    return this->x;
}
double Ball::get_y()
{
    return this->y;
}
double Ball::get_vx()
{
    return this->vx;
}
double Ball::get_vy()
{
    return this->vy;
}

void Ball::set_x(double _x)
{
    this->x = _x;
}
void Ball::set_y(double _y)
{
    this->y = _y;
}
void Ball::set_vx(double _vx)
{
    this->vx = _vx;
}
void Ball::set_vy(double _vy)
{
    this->vy = _vy;
}