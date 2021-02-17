
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
	Tetrimino *piece;
	bool up, down, left, right;
	SDL_TimerID timer;
	SDL_TimerID timer_screen;
	// + ?

public:
	inline Game()
	{
	}

	void init();

	//void draw(double dt);

	bool keyboard(const Uint8 key);

	void loop();

	void update();

	void reset_key();

	bool check_event(SDL_Event event);

	static Uint32 update_timer_callback(Uint32 intervalle, void *parametre);
	static Uint32 refresh_screen_callback(Uint32 intervalle, void *parametre);
};

void Game::init()
{
	win = new WindowSurface;
	planche = new Sprite("./sprites.bmp");
	piece = new Tetrimino(14, 6, 3, L_REVERSE, BLUE);
	piece->print_tetrimino();
	left = false;
	right = false;
	up = false;
	down = false;
}

void Game::reset_key()
{
	left = false;
	right = false;
	up = false;
	down = false;
}

bool Game::check_event(SDL_Event event)
{
	bool quit = false;
	switch (event.type)
	{
	case SDL_QUIT:
		quit = true;
		break;
	case SDL_MOUSEBUTTONDOWN:
		printf("mouse click %d\n", event.button.button);
		break;
	case SDL_KEYUP: //DOWN
		quit = keyboard(event.key.keysym.scancode);
	}
	return quit;
}

bool Game::keyboard(const Uint8 key)
{
	bool quit = false;
	switch (key)
	{
	case SDL_SCANCODE_LEFT:
		printf("left\n");
		left = true;
		break;
	case SDL_SCANCODE_RIGHT:
		printf("right\n");
		right = true;
		break;
	case SDL_SCANCODE_UP:
		printf("up\n");
		up = true;
		break;
	case SDL_SCANCODE_DOWN:
		printf("down\n");
		down = true;
		break;
	case SDL_SCANCODE_SPACE:
		printf("espace");
		quit = true;
		break;
	default:
		break;
	}
	return quit;
}

void Game::update()
{
	piece->move(left, right, down, up);
}

Uint32 Game::update_timer_callback(Uint32 intervalle, void *parametre)
{
	Tetrimino *piece = static_cast<Tetrimino *>(parametre);
	piece->move_down();
	printf("timer appelé\n");
	return intervalle;
}

void Game::loop()
{
	int prev = 0, now = 0;
	bool quit = false;
	timer = SDL_AddTimer(1000, update_timer_callback, piece); /* Démarrage du timer */
	while (!quit)
	{
		now = SDL_GetTicks();
		SDL_Event event;
		while (!quit && SDL_PollEvent(&event))
		{
			quit = check_event(event);
			update();
			win->render(piece, planche->get_surf());
			reset_key();
		}
		if (now - prev > 30)
		{
			win->render(piece, planche->get_surf());
			prev = now;
		}
	}
	SDL_Quit();
}

int main(int argc, char **argv)
{
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS) != 0)
	{
		return 1;
	}

	Game g;

	g.init();
	g.loop();
	cout << "fin du jeu" << endl;
}
