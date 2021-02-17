
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
	piece = new Tetrimino(0, 0, 3, L_REVERSE, BLUE);
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

// Uint32 Game::update_timer_callback(Uint32 intervalle, void *parametre)
// {
// 	Tetrimino *piece = static_cast<Tetrimino *>(parametre);
// 	piece->move_down();
// 	printf("timer appelé\n");
// 	// win->render(piece, planche->get_surf());
// 	return intervalle;
// }


// Uint32 Game::refresh_screen_callback(Uint32 intervalle, void *parametre)
// {
// 	WindowSurface *win_timer = static_cast<WindowSurface*>(parametre);
// 	Tetrimino* piece_timer 
// 	win_timer->render(piece, planche->get_surf());
// 	return intervalle;
// }

// void Game::draw(double dt)
// {
// 	// remplit le fond
// 	SDL_Rect dest = {0, 0, 0, 0};
// 	for (int j = 0; j < win->get_surf()->h; j += 128)
// 	{
// 		for (int i = 0; i < win->get_surf()->w; i += 96)
// 		{
// 			dest.x = i;
// 			dest.y = j;
// 			// copie depuis la planche de sprite vers la fenetre
// 			SDL_BlitSurface(planche->get_surf(), &planche->srcBg, win->get_surf(), &dest);
// 		}
// 	}
// }

void Game::loop()
{

	Uint64 prev, now = SDL_GetPerformanceCounter(); // timers
	double delta_t;									// durée frame en ms
	bool quit = false;
	// timer = SDL_AddTimer(2000, update_timer_callback, piece); /* Démarrage du timer */
	// timer_screen = refresh_screen_callback(1000/30, win);
	while (!quit)
	{
		SDL_Event event;
		while (!quit && SDL_PollEvent(&event))
		{
			quit = check_event(event);
			update();
			win->render(piece, planche->get_surf());
			reset_key();
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
