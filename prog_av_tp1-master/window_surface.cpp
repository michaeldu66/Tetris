#include "window_surface.h"
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

void WindowSurface::render(Tetrimino* shape)
{
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255); // render, rgb, opaque, on le met noir 
    SDL_RenderClear(rend);                        /* Clear the entire screen to our selected color. */
    shape->draw(rend);
    SDL_RenderPresent(rend);                        /* show the result on the screen */
}