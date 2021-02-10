#ifndef _WINDOW_SURFACE_
#define _WINDOW_SURFACE_
using namespace std;

#include <SDL.h>
#include "surface.h"
#include "tetrimino.h"
#include <iostream>
class Sprite;
class Surface;
class WindowSurface : public Surface
{
protected:
    SDL_Window *pWindow;
    SDL_Renderer *rend;

public:
    SDL_Window *get_w();
    void render(Tetrimino* shape);
    WindowSurface() : Surface()
    {
        this->pWindow = SDL_CreateWindow("Tetris- Made By Hofmann & Berthault", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
        rend = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        cout << "Renderer created" << endl;
        this->set_surf(pWindow);
        cout << "winSurface created" << endl;
    }
};

#endif