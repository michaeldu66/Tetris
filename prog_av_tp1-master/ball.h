#ifndef _BALL_H_
#define _BALL_H_
#include <SDL.h>
#include <iostream>
using namespace std;
class Ball
{
    protected:
        double x; 
        double y;
        double vx;
        double vy;
        SDL_Rect* srcBall;

    public :

        Ball(double _x, double _y, double _vx, double _vy);

        double get_x();
        double get_y();
        double get_vx();
        double get_vy();


        void set_x(double _x);
        void set_y(double _y);
        void set_vx(double _vx);
        void set_vy(double _vy);
} ;

#endif
