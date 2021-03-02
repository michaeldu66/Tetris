#include "window_surface.h"
#include "tetrimino.h"
WindowSurface::WindowSurface() : Surface()
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

SDL_Window *WindowSurface::get_w()
{
    return this->pWindow;
}

void WindowSurface::render(Tetrimino *shape, SDL_Surface *spriteBg, Board *board)
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
    //shape->draw(rend);

    /***
     * SDL Surface* mytext;
     * SDL_Rect position;
     * SDL_Texture* RealText;
     * 
     * 
     * et ya ça dans le constructeur
     * 
     * police = TTF_OpenFont("src/Valentime.otf", 80);
     * colorPolice = {255, 255, 255};
     * strncpy(msg, "Score ", 100);
     * msg[strlen(msg) - 1] = '\0';

     * ***/

    board->printScoreToScreen(rend);
    SDL_RenderPresent(rend); /* show the result on the screen */
    board->freeScoreText();
}