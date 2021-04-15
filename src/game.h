#ifndef _GAMETETRIS_
#define _GAMETETRIS_
#include <SDL.h>
#include <string>
#include <iostream>

#include "window_surface.h"
#include "sprite.h"
#include "tetrimino.h"
#include "board.h"
#include "virtualPlayer.h"

class Game
{
private:
	WindowSurface *win;
	Sprite *planche;
	Tetrimino *piece;
	Board * Player_board;
	Board * IA_board;
	MOV_DIRECTION direction;
	SDL_TimerID timer_descente_Player;
	SDL_TimerID timer_descente_IA;
	//SDL_TimerID timer_screen;
	static bool isPaused;
	static bool menuMode;
	static bool IAMode;

	Mix_Music *music; //Création du pointeur de type Mix_Music

	/***
	 * partie IA
	 * ***/

	virtualPlayer* IAPlayer;


public:
	inline Game(){}

	void init();

	bool keyboard(const Uint8 key);

	void loop();

	bool IsGameOver(Board* board_);

	bool update(Board* board_);

	void reset_key();

	bool check_event(SDL_Event event);

	static Uint32 update_timer_descente_callback(Uint32 intervalle, void *parametre);
	static Uint32 update_timer_fixation_callback(Uint32 intervalle, void* parametre);
	static Uint32 refresh_screen_callback(Uint32 intervalle, void *parametre);
};
#endif