#ifndef _WINDOW_SURFACE_
#define _WINDOW_SURFACE_
using namespace std;

#include <SDL.h>
#include "surface.h"
#include <iostream>
class Sprite;
class Surface;
class WindowSurface : public Surface
{
protected:
    SDL_Window *pWindow;

public:
    SDL_Window* get_w();
    WindowSurface() : Surface()
    {
        this->pWindow = SDL_CreateWindow("Hofmann_Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
        this->set_surf(pWindow);
        cout << "winSurface created" << endl;
    }
};

#endif