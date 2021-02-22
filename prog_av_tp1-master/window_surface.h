#ifndef _WINDOW_SURFACE_
#define _WINDOW_SURFACE_
using namespace std;
#include <SDL.h>
#include "surface.h"
#include "tetrimino.h"
#include "board.h"
#include <iostream>

#define WIN_W 990
#define WIN_H 990

class Board;
class Sprite;
class Surface;
class WindowSurface : public Surface
{
protected:
    SDL_Window *pWindow;
    SDL_Renderer *rend;
    SDL_Texture *Bg;
    SDL_Rect *carre_grill;

public:
    SDL_Window *get_w();
    void render(Tetrimino *shape, SDL_Surface *spriteBg, Board* board);
    WindowSurface() : Surface()
    {
        this->pWindow = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
        rend = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        cout << "Renderer created" << endl;
        this->set_surf(pWindow);
        cout << "winSurface created" << endl;
        carre_grill = new SDL_Rect();
        carre_grill->h = TETR_SIZE;
        carre_grill->w = TETR_SIZE;
    }
};

#endif