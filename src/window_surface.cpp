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

    //Affichage du mode menu
    police = TTF_OpenFont("src/GUNSHIP2.TTF", 20);
    colorPolice = {74, 69, 68};
    positionMenuInfos = new SDL_Rect();
    textButtonSurface = new SDL_Surface();

    menuBackgroundSprite = IMG_Load("src/tetrisLogo.png");
    if (menuBackgroundSprite == nullptr)
    {
        cout << "IMG_Load: " << IMG_GetError() << "\n";
    }
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

void WindowSurface::render(SDL_Surface *spriteBg, Board *board, bool isPaused, bool menuMode)
{
    if (menuMode)
    {
        drawMenuScreen();
        SDL_RenderPresent(rend);
        return;
    }
    backgroundRender(spriteBg);
    board->draw_board(rend);
    board->printInfosToScreen(rend);
    if (isPaused)
        drawPauseScreen();
    SDL_RenderPresent(rend); /* show the result on the screen */
    board->freeScoreText();
}

/***
 *Ecris le texte d'affichage de l'option dans un buffer 
 ***/
void WindowSurface::textMenuInfos(menuInfo infos)
{
    switch (infos)
    {
    case RESUME:
        snprintf(menuMsg, 100, "RESUME");
        break;
    case QUIT:
        snprintf(menuMsg, 100, "QUIT");
        break;
    case PLAY:
        snprintf(menuMsg, 100, "PLAY");
        break;
    case EXIT:
        snprintf(menuMsg, 100, "EXIT");
        break;
    case COPYRIGHT:
        snprintf(menuMsg, 100, "MaADE By Hofmann Michael AND Berthault Dylan");
        break;
    }
    menuMsg[strlen(menuMsg)] = '\0';
}

void WindowSurface::setPositionInfos(menuInfo infos)
{
    if (infos == COPYRIGHT)
    {
        positionMenuInfos->w = WIN_W/ 2;
        positionMenuInfos->h = pauseRect->h / 7;
        positionMenuInfos->x = WIN_W/2 ;
        positionMenuInfos->y = WIN_H - positionMenuInfos->h;
        return;
    }
    positionMenuInfos->w = pauseRect->w / 2;
    positionMenuInfos->h = pauseRect->h / 7;
    positionMenuInfos->x = pauseRect->x + (pauseRect->w / 2 - positionMenuInfos->w / 2);
    positionMenuInfos->y = pauseRect->h + (int(infos) + 1) * (positionMenuInfos->h + pauseRect->h / 7);
}
// affiche le grand rectangle du mode pause
void WindowSurface::drawBackgroundPauseScreen()
{
    SDL_SetRenderDrawColor(rend, 213, 213, 213, 255);
    SDL_RenderFillRect(rend, pauseRect);
}

void WindowSurface::drawButtonsPauseScreen()
{
    for (menuInfo infos = RESUME; infos < 2; infos = menuInfo(int(infos) + 1))
    {
        textMenuInfos(infos);
        textButtonSurface = TTF_RenderText_Solid(police, menuMsg, colorPolice);
        setPositionInfos(infos);
        textButtonTexture = SDL_CreateTextureFromSurface(rend, textButtonSurface);

        SDL_SetRenderDrawColor(rend, 213, 213, 213, 255); // background of text
        SDL_RenderFillRect(rend, positionMenuInfos);
        SDL_SetRenderDrawColor(rend, 150, 150, 150, 255); //contour du menu
        SDL_RenderDrawRect(rend, positionMenuInfos);

        SDL_RenderCopy(rend, textButtonTexture, NULL, positionMenuInfos);
    }
}

// Affiche les différents boutons
void WindowSurface::drawPauseScreen()
{
    drawBackgroundPauseScreen();
    drawButtonsPauseScreen();
}

bool WindowSurface::xInsideResumeButton(int x)
{
    return x > positionMenuInfos->x && x < positionMenuInfos->x + positionMenuInfos->w ? true : false;
}

bool WindowSurface::yInsideResumeButton(int y, menuInfo infosM)
{
    return (y > (pauseRect->h + (int(infosM) + 1) * (positionMenuInfos->h + pauseRect->h / 7)) && (y < (pauseRect->h + (int(infosM) + 1) * (positionMenuInfos->h + pauseRect->h / 7) + positionMenuInfos->h))) ? true : false;
}

bool WindowSurface::isInsideResumeButtom(int x, int y, menuInfo infosM)
{
    return (xInsideResumeButton(x) && yInsideResumeButton(y, infosM));
}

void WindowSurface::drawBackgroundMenuScreen()
{
    //background light white
    SDL_Rect menuBg;
    menuBg.x = 0;
    menuBg.y = 0;
    menuBg.w = WIN_W;
    menuBg.h = WIN_H;

    SDL_SetRenderDrawColor(rend, 213, 213, 213, 255);
    SDL_RenderFillRect(rend, &menuBg);
    SDL_RenderDrawRect(rend, &menuBg);

    //IMAGE
    SDL_Rect srcMenuBg = {128, 57, 568, 198};
    Bg = SDL_CreateTextureFromSurface(rend, menuBackgroundSprite); // récupère la surface du sprite en tant que texture
    if (Bg == nullptr)
        printf("error creation texture\n");

    SDL_Rect dest = {WIN_W / 2 - srcMenuBg.w / 2, WIN_H / 3, 600, 200};
    SDL_RenderCopy(rend, Bg, &srcMenuBg, &dest);
}

void WindowSurface::drawButtonsMenuScreen()
{
    for (menuInfo infos = PLAY; infos < 5; infos = menuInfo(int(infos) + 1))
    {
        textMenuInfos(infos);
        textButtonSurface = TTF_RenderText_Solid(police, menuMsg, colorPolice);
        setPositionInfos(infos);
        textButtonTexture = SDL_CreateTextureFromSurface(rend, textButtonSurface);

        SDL_SetRenderDrawColor(rend, 150, 150, 150, 255); // background of text
        SDL_RenderDrawRect(rend, positionMenuInfos);
        SDL_RenderCopy(rend, textButtonTexture, NULL, positionMenuInfos);
    }
}

void WindowSurface::drawMenuScreen()
{
    drawBackgroundMenuScreen();
    drawButtonsMenuScreen();
}