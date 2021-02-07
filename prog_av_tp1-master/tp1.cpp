
#include <SDL.h>
#include <string>
#include <iostream>

#include "window_surface.h"
#include "sprite.h"
#include "ball.h"

class Game
{
	WindowSurface *win;
	Sprite *planche;

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

int showmenu(SDL_Surface *screen, TTF_Font *font)
{
	//classe avec labels, menus, selected, pos et array de ça
	Uint32 time;
	int x, y;
	const int NUMMENU = 2;
	const char *labels[NUMMENU] = {"Continue", "Exit"};
	SDL_Surface *menus[NUMMENU]; // surface for the menu
	bool selected[NUMMENU] = {0, 0};
	SDL_COLOR color[2] = {{255, 255, 255}, {2555, 0, 0}};

	menus[0] = TTF_RenderText_Solid(font, labels[0], color[0]);
	menus[1] = TTF_RenderText_Solid(font, labels[1], color[0]);

	SDL_Rect pos[NUMMENU];
	pos[0].x = screen->clip_rect.w / 2 - menu[0]->clip_rect.w / 2;
	pos[0].y = screen->clip_rect.h / 2 - menu[0]->clip_rect.h / 2;

	pos[1].x = screen->clip_rect.w / 2 - menu[0]->clip_rect.w / 2;
	pos[1].y = screen->clip_rect.h / 2 - menu[0]->clip_rect.h / 2;

	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00)); // fill the screen with  black 

	SDL_Event event;
	while (1)
	{
		time = SDL_GetTicks();
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				for (int i = 0; i < NUMMENU; i++)
				{
					SDL_FreeSurface(menu[i]);
				}
				return 1;
			case SDL_MOUSEMOTION:
				x = event.motion.x;
				y = event.motion.y;
				for (int i = 0; i < NUMMENU; i++)
				{
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
					{
						if (!selected[i])
						{
							selected[i] = 1;
							SDL_FREESurface(menus[i]);
							menu[î] = TTF_RenderText_Solid(font, menus[i], color[1]);
						}
					}
					else
					{
						if (selected[i])
						{
							selected[i] = 0;
							SDL_FREESurface(menus[i]);
							menu[î] = TTF_RenderText_Solid(font, menus[i], color[0]);
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = event.button.x;
				y = event.button.y;
				for (int i = 0; i < NUMMENU; i++)
				{
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
						return i;
				}
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPTE) //si on appuie sur esc
					return 0;
			break;
			}
		}
	}
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
