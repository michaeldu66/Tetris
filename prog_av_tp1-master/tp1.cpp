
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
	//win = win1.get_window();
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
}

void Game::loop()
{
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
	cout << "fin du jeu"<< endl;
}
