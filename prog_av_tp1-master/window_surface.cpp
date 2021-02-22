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

    /** grille noire normalement, mais ne pas decommenter sinon ya tout qui ramne de ouf**/
    // for (int i = 180; i < WIN_H - 180; i=i+30) //centrée en hauteur
    // {
    //     for (int j = 330; j < WIN_W - 330; j=j+30)
    //     {

    //         carre_grill->x = j ;
    //         carre_grill->y = i ;
    //         SDL_SetRenderDrawColor(rend, 75, 75, 75, 0); // inside of squares black
    //         SDL_RenderFillRect(rend, carre_grill);
    //         SDL_SetRenderDrawColor(rend, 219, 219, 219, 255);
    //         SDL_RenderDrawRect(rend, carre_grill); //borderline of squares (in white)
    //     }
    // }
    board->draw_board(rend);

    //SDL_RenderPresent(rend); /* show the result on the screen of the background */

    //SDL_SetRenderDrawColor(rend, 0, 0, 0, 255); // render, rgb, opaque, on le met noir
    //SDL_RenderClear(rend);                      /* Clear the entire screen to our selected color. */
    shape->draw(rend);
    SDL_RenderPresent(rend); /* show the result on the screen */
}