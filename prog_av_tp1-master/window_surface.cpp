#include "window_surface.h"
#include "tetrimino.h"
SDL_Window *WindowSurface::get_w()
{
    return this->pWindow;
}

void WindowSurface::render(Tetrimino *shape, SDL_Surface *spriteBg, Board* board)
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

    board->draw_board(rend);
    shape->draw(rend);
    SDL_RenderPresent(rend); /* show the result on the screen */
}