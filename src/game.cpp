// rayanlegris@gmail.com
#include "game.h"

bool Game::isPaused; // car variable static pour l'utiliser dans le callback

void Game::init()
{
	win = new WindowSurface;
	planche = new Sprite("src/sprites.bmp");
	board = new Board();
	piece = board->getCurrentPiece();
	direction = NO_MOVE;
	isPaused = false;
	//SDL_WM_SetCaption("SDL_Mixer", NULL);
	//music = sizeof(Mix_Music);
	music = Mix_LoadMUS("tetrisSong.mp3");
	if (!music)
		printf("Mix_LoadMUS(\"music.mp3\"): %s\n", Mix_GetError());
	Mix_PlayMusic(music, -1);
}

void Game::reset_key()
{
	direction = NO_MOVE;
}

bool Game::check_event(SDL_Event event)
{
	bool quit = false;
	int xMouse, yMouse;
	// if(event.window.event == SDL_WINDOWEVENT_CLOSE)
	// 	return true;

	switch (event.type)
	{
	case SDL_QUIT:
		quit = true;
		break;
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&xMouse, &yMouse);
		menuInfo infos;
		if (isPaused)
		{
			infos = RESUME;
			if (win->isInsideResumeButtom(xMouse, yMouse, infos))
				isPaused = false;
			infos = QUIT;
			if (win->isInsideResumeButtom(xMouse, yMouse, infos))
				quit = true;
		}
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
	if (isPaused && (key != SDL_SCANCODE_P))
		return false;

	switch (key)
	{
	case SDL_SCANCODE_P:
		printf("on fait pause");
		isPaused = !isPaused;
		break;
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
	if (!isPaused)
	{
		myboard->update_direction(DOWN);
		if (!myboard->DetectCollision())
			myboard->moveCurrentPiece();
	}

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
		now = SDL_GetTicks();

		//update();
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			if (check_event(event))
				break;
			if (!isPaused && update())
				break;
			reset_key();
		}
		if (now - prev > 30) // timer pour le FPS
		{
			cpt++;
			if (!isPaused)
			{
				quit = update();
				win->render(planche->get_surf(), board, false);
				board->print_piece_to_board();
			}
			else
			{
				win->render(planche->get_surf(), board, true);
			}
			prev = now;
			if (cpt % 100 == 0)
				board->print_board();
		}
	}
	//TTF_CloseFont(police); /* Doit être avant TTF_Quit() */
	Mix_FreeMusic(music); //Libération de la musique
	Mix_CloseAudio();	  //Fermeture de l'API
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

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
	{
		printf("%s", Mix_GetError());
	}

	Game g;

	g.init();
	g.loop();
	cout << "fin du jeu" << endl;
}
