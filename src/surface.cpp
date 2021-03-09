#include "surface.h"

Surface::Surface()
{
    this->surf = NULL;
    cout << "surface créée" << endl;
}

void Surface::set_surf(const char* link_sprite)
{
    this->surf = SDL_LoadBMP(link_sprite);
    cout << "surface modifiée avec sprite" << endl;
}
void Surface::set_surf(SDL_Window *pWindow)
{
    this->surf = SDL_GetWindowSurface(pWindow);
    cout << "surface modifiée avec pwindow" << endl;
}

SDL_Surface* Surface::get_surf()
{
    return this->surf;
}