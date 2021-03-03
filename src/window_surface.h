#ifndef _WINDOW_SURFACE_
#define _WINDOW_SURFACE_
using namespace std;
#include <SDL.h>
#include "surface.h"
#include "tetrimino.h"
#include "board.h"
#include <iostream>
#include <SDL2/SDL.h>

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
    SDL_Rect *pauseRect;

public:
    WindowSurface();
    SDL_Window *get_w();
    void render(SDL_Surface *spriteBg, Board *board, bool isPaused);
    void backgroundRender(SDL_Surface *spriteBg);
    void drawPauseScreen();
};

#endif