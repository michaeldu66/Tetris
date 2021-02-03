#include <SDL.h>
#include <iostream>
#include <cmath>

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

SDL_Window* pWindow = NULL;
SDL_Surface* win_surf = NULL;
SDL_Surface* plancheSprites = NULL;

// coordonnées des sprites dans l'image
// x,y, w,h (0,0) en haut a gauche
SDL_Rect srcBg = { 0,128, 96,128 }; 
SDL_Rect srcBall = { 0,96,24,24 };

// Ball = position x,y  + vitesse vx,vy
struct { double x; double y;  double vx; double vy; } ball;


void init()
{
	// creation fenetre
	pWindow = SDL_CreateWindow("Arknoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);
	// creation d'une "surface" à patir d'une image
	plancheSprites = SDL_LoadBMP("./sprites.bmp");

	// definit la souleur transparente
	SDL_SetColorKey(plancheSprites, true, 0);  // 0: 00/00/00 noir -> transparent

	// place la balle u milieu
	int w, h;
	SDL_GetWindowSize(pWindow, &w, &h);
	ball.x =  w / 2;
	ball.y = h / 2;
	ball.vx = 40;
	ball.vy = 25;
}

void keyboard(const Uint8* keys)
{
	//if (keys[SDL_SCANCODE_RETURN])
	//	std::cout<< "<RETURN> is pressed."<< std::endl;

	if (keys[SDL_SCANCODE_SPACE])
	{
		int w, h;
		SDL_GetWindowSize(pWindow, &w, &h);
		ball.x = w / 2;
		ball.y = h / 2;
	}

	if (keys[SDL_SCANCODE_UP])
		ball.vy -= 0.2;

	if (keys[SDL_SCANCODE_DOWN])
		ball.vy += 0.2;
		
	if (keys[SDL_SCANCODE_LEFT])
		ball.vx -= 0.2;

	if (keys[SDL_SCANCODE_RIGHT] )
		ball.vx += 0.2;
}

// fonction qui met à jour la surface de la fenetre "win_surf"
void draw(double dt)
{
	// remplit le fond 
	SDL_Rect dest = { 0,0,0,0 };
	for (int j = 0; j < win_surf->h; j += 128)
		for (int i = 0; i < win_surf->w; i += 96)
		{
			dest.x = i;
			dest.y = j;
			// copie depuis la planche de sprite vers la fenetre
			SDL_BlitSurface(plancheSprites, &srcBg, win_surf, &dest);
		}

		// affiche balle
	SDL_Rect dstBall = { int(ball.x), int(ball.y), 0, 0 };
	SDL_BlitSurface(plancheSprites, &srcBall, win_surf, &dstBall);

	// deplacement (*dt pour vitesse constante)
	ball.x += ball.vx * dt;
	ball.y += ball.vy * dt;

	// collision bord
	int w, h;
	SDL_GetWindowSize(pWindow, &w, &h);
	if ((ball.x < 1) || (ball.x > (w - 25)))
		ball.vx *= -1;
	if ((ball.y < 1) || (ball.y > (h - 25)))
		ball.vy *= -1;
}



int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return 1;
	}

	init();

	Uint64 prev, now = SDL_GetPerformanceCounter(); // timers
	double delta_t;  // durée frame en ms

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		while (!quit && SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				printf("mouse click %d\n", event.button.button);
				break;
			default: break;
			}
		}

		const Uint8* state = SDL_GetKeyboardState(NULL);
		keyboard(state);
		quit |= (state[SDL_SCANCODE_ESCAPE]!=0);

		prev = now;
		now = SDL_GetPerformanceCounter();
		delta_t = (double)((now - prev) / (double)SDL_GetPerformanceFrequency());

		draw(delta_t);
		// affiche la surface
		SDL_UpdateWindowSurface(pWindow);

	}
	SDL_Quit();
	return 0;
}

