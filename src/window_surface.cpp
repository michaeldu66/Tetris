#include "window_surface.h"
#include "tetrimino.h"
WindowSurface::WindowSurface() : Surface()
{
    this->pWindow = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
    rend = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    cout << "Renderer created" << endl;
    this->set_surf(pWindow);
    cout << "winSurface created" << endl;

    pauseRect = new SDL_Rect();
    pauseRect->h = WIN_W / 3;
    pauseRect->w = WIN_H / 2;
    pauseRect->y = WIN_W / 2 - pauseRect->h / 2;
    pauseRect->x = WIN_W / 2 - pauseRect->w / 2;
}

SDL_Window *WindowSurface::get_w()
{
    return this->pWindow;
}

void WindowSurface::backgroundRender(SDL_Surface *spriteBg)
{
    SDL_Rect srcBg = {0, 128, 96, 128};
    Bg = SDL_CreateTextureFromSurface(rend, spriteBg); // récupère la surface du sprite en tant que texture
    if (Bg == nullptr)
        printf("error creation texture\n");

    SDL_Rect dest = {0, 0, 128, 96};
    for (int i = 0; i < get_surf()->h; i += 128)
    {
        for (int j = 0; j < get_surf()->w; j += 96)
        {
            dest.x = i;
            dest.y = j;
            // copie depuis la planche de sprite vers le render
            SDL_RenderCopy(rend, Bg, &srcBg, &dest);
        }
    }
}

// void WindowSurface::pauseRender(SDL_Surface *spriteBg){
//     WindowSurface::backgroundRender(spriteBg);
// }

void WindowSurface::render(SDL_Surface *spriteBg, Board *board, bool isPaused)
{
    WindowSurface::backgroundRender(spriteBg);
    board->draw_board(rend);
    board->printInfosToScreen(rend);
    if (isPaused)
        drawPauseScreen();
    SDL_RenderPresent(rend); /* show the result on the screen */
    board->freeScoreText();
}

void WindowSurface::drawPauseScreen()
{
    SDL_SetRenderDrawColor(rend, 88, 85, 84, 255);
    SDL_RenderFillRect(rend, pauseRect);
    SDL_SetRenderDrawColor(rend, 190, 190, 190, 0); //contour du menu
    SDL_RenderDrawRect(rend, pauseRect);
}