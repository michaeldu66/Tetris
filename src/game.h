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
	/***
	 * planche is for the blue background
	 * piece is the current piece mooving down
	 * direction represent the key the player is playing (RIGHT, LEFT,...)
	 * ***/
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

	/***
	 * Create the windows, blue background, board(s)
	 * and launch the music.
	 * ***/
	void init();

	/***
	 * collect all the key pressed by the player
	 * ***/
	bool keyboard(const Uint8 key);

	/***
	 * Launch the whole process of the game,
	 * deals with timer, FPS, menuMode, detection, etc..
	 * ***/
	void loop();

	/***
	 * Indicate when the game is done 
	 * ie a piece touch the top of the screen
	 * ***/
	bool IsGameOver(Board* board_);

	bool update();
	//bool update(Board* board_);
	//bool update(Board* Playerboard_, Board* IAboard_);
	void reset_key();

	bool check_event(SDL_Event event);

	static Uint32 update_timer_descente_callback(Uint32 intervalle, void *parametre);
	static Uint32 update_timer_fixation_callback(Uint32 intervalle, void* parametre);
	static Uint32 refresh_screen_callback(Uint32 intervalle, void *parametre);
};
#endif