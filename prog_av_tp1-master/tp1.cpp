
#include <SDL.h>
#include <string>
#include <iostream>

#include "window_surface.h"
#include "sprite.h"
#include "ball.h"
#include "tetrimino.h"

// rayanlegris@gmail.com
class Game
{
	WindowSurface *win;
	Sprite *planche;
	Tetrimino* piece;
	// + ?

public:
	inline Game()
	{
	}

	void init();

	void draw(double dt);

	void keyboard(const Uint8 *keys);

	void loop();
};

void Game::init()
{
	win = new WindowSurface;
	planche = new Sprite("./sprites.bmp");
	piece = new Tetrimino(0, 0, 3, L_REVERSE, RED);
	piece->print_tetrimino();
}

void Game::keyboard(const Uint8 *keys)
{
	//	if (keys[SDL_SCANCODE_SPACE])
	//
	//	if (keys[SDL_SCANCODE_UP])
	//
}

void Game::draw(double dt)
{
	// remplit le fond
	SDL_Rect dest = {0, 0, 0, 0};
	for (int j = 0; j < win->get_surf()->h; j += 128)
		for (int i = 0; i < win->get_surf()->w; i += 96)
		{
			dest.x = i;
			dest.y = j;
			// copie depuis la planche de sprite vers la fenetre
			SDL_BlitSurface(planche->get_surf(), &planche->srcBg, win->get_surf(), &dest);
		}
}

void Game::loop()
{

	Uint64 prev, now = SDL_GetPerformanceCounter(); // timers
	double delta_t;									// durée frame en ms
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
			default:
				break;
			}
		}

		const Uint8 *state = SDL_GetKeyboardState(NULL);
		keyboard(state);
		quit |= (state[SDL_SCANCODE_ESCAPE] != 0);

		prev = now;
		now = SDL_GetPerformanceCounter();
		delta_t = (double)((now - prev) / (double)SDL_GetPerformanceFrequency());
		draw(delta_t);
		// affiche la surface
		SDL_UpdateWindowSurface(win->get_w());
	}
	SDL_Quit();
}

int main(int argc, char **argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return 1;
	}

	Game g;

	g.init();
	g.loop();
	cout << "fin du jeu" << endl;
}
