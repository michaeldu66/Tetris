#include "window_surface.h"
#include "surface.h"
#include "tetrimino.h"
// WindowSurface::WindowSurface() : Surface()
// {
//     this->pWindow = SDL_CreateWindow("Hofmann_Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
//     this->set_surf(pWindow);
//     cout << "winSurface created" << endl;
// }

// SDL_Window* WindowSurface::get_w(){
//     return this->pWindow;
// }

SDL_Window *WindowSurface::get_w()
{
    return this->pWindow;
}

void WindowSurface::render(Tetrimino *shape, SDL_Surface *spriteBg)
{
    SDL_Rect srcBg = {0, 128, 96, 128};
    Bg = SDL_CreateTextureFromSurface(rend, spriteBg); // récupère la surface du sprite en tant que texture
    if(Bg == nullptr)
        printf("error creation texture\n");
    SDL_Rect dest = {0, 0, 128, 96};
    for (int j = 0; j < get_surf()->h; j += 128)
    {
        for (int i = 0; i < get_surf()->w; i += 96)
        {
            dest.x = j;
            dest.y = i;
            // copie depuis la planche de sprite vers le render
            SDL_RenderCopy(rend, Bg, &srcBg, &dest);
        }
    }
    SDL_RenderPresent(rend); /* show the result on the screen of the background */

    //SDL_SetRenderDrawColor(rend, 0, 0, 0, 255); // render, rgb, opaque, on le met noir
    //SDL_RenderClear(rend);                      /* Clear the entire screen to our selected color. */
    shape->draw(rend);
    SDL_RenderPresent(rend); /* show the result on the screen */
}
