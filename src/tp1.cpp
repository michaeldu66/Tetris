
#include <SDL.h>
#include <string>
#include <iostream>

#include "window_surface.h"
#include "sprite.h"
#include "tetrimino.h"
#include "board.h"

// rayanlegris@gmail.com
class Game
{
	WindowSurface *win;
	Sprite *planche;
	Tetrimino *piece;
	Board *board;
	MOV_DIRECTION direction;
	SDL_TimerID timer;
	SDL_TimerID timer_screen;
	// + ?

public:
	inline Game()
	{
	}

	void init();

	bool keyboard(const Uint8 key);

	void loop();

	bool update();

	void reset_key();

	bool check_event(SDL_Event event);

	static Uint32 update_timer_callback(Uint32 intervalle, void *parametre);
	static Uint32 refresh_screen_callback(Uint32 intervalle, void *parametre);
};

void Game::init()
{
	win = new WindowSurface;
	planche = new Sprite("src/sprites.bmp");
	board = new Board();
	piece = board->getCurrentPiece();
	direction = NO_MOVE;
}

void Game::reset_key()
{
	direction = NO_MOVE;
}

bool Game::check_event(SDL_Event event)
{
	bool quit = false;

	// if(event.window.event == SDL_WINDOWEVENT_CLOSE)
	// 	return true;

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
		direction = LEFT;
		break;
	case SDL_SCANCODE_RIGHT:
		direction = RIGHT;
		break;
	case SDL_SCANCODE_UP:
		direction = UP;
		break;
	case SDL_SCANCODE_DOWN:
		direction = DOWN;
		break;
	case SDL_SCANCODE_SPACE:
		direction = FAR_DOWN;
		break;
	case SDL_SCANCODE_ESCAPE:
		printf("escape");
		quit = true;
		break;
	default:
		break;
	}
	return quit;
}

bool Game::update()
{
	board->update_direction(direction);
	if (board->IsGameOver())
		return true;

	if (!board->DetectCollision())
		board->moveCurrentPiece();
	else if (board->getCurrentPiece()->getStateFinished())
	{
		board->print_piece_to_background(); // print la pièce dans le background avant de générer la suivante
		board->LineFull();					//Efface les lignes pleines
		piece = board->GenerateRandomShape();
	}
	return false;
}

Uint32 Game::update_timer_callback(Uint32 intervalle, void *parametre)
{
	Board *myboard = static_cast<Board *>(parametre);
	myboard->update_direction(DOWN);
	if (!myboard->DetectCollision())
		myboard->moveCurrentPiece();
	//printf("timer appelé\n");
	return intervalle;
}

void Game::loop()
{
	int cpt = 0;
	int prev = 0, now = 0;
	bool quit = false;
	timer = SDL_AddTimer(1000, update_timer_callback, board); /* faire descendre la piece toutes les secondes*/
	while (!quit)
	{
		//update();
		now = SDL_GetTicks();
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			if (check_event(event))
				break;
			if (update())
				break;
			reset_key();
		}
		if (now - prev > 30) // timer pour le FPS
		{
			cpt++;
			quit = update();
			win->render(piece, planche->get_surf(), board);
			board->print_piece_to_board();
			prev = now;
			if (cpt % 100 == 0)
				board->print_board();
		}
	}
	//TTF_CloseFont(police); /* Doit être avant TTF_Quit() */
	TTF_Quit();
	SDL_Quit();
}

int main(int argc, char **argv)
{
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS) != 0)
	{
		return 1;
	}

	if (TTF_Init() == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

	Game g;

	g.init();
	g.loop();
	cout << "fin du jeu" << endl;
}
