// rayanlegris@gmail.com
#include "game.h"

bool Game::isPaused; // car variable static pour l'utiliser dans le callback
bool Game::menuMode; // car variable static pour l'utiliser dans le callback
bool Game::IAMode;

void Game::init()
{
	win = new WindowSurface;
	planche = new Sprite("src/sprites.bmp");
	board = new Board();
	piece = board->getCurrentPiece();
	direction = NO_MOVE;
	board->print_piece_to_next();
	isPaused = false;

	music = Mix_LoadMUS("tetrisSong.mp3");
	if (!music)
		printf("Mix_LoadMUS(\"music.mp3\"): %s\n", Mix_GetError());
	//Mix_PlayMusic(music, -1);
	menuMode = true;

	IAPlayer = new virtualPlayer(board);
	IAMode = false;
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
		if (menuMode)
		{
			infos = PLAY;
			if (win->isInsideResumeButtom(xMouse, yMouse, infos))
				menuMode = false;
			infos = IA;
			if (win->isInsideResumeButtom(xMouse, yMouse, infos))
			{
				menuMode = false;
				IAMode = true;
				printf("mode IA enclenché\n");
			}
			infos = EXIT;
			if (win->isInsideResumeButtom(xMouse, yMouse, infos))
				quit = true;
		}
		else if (isPaused)
		{
			infos = RESUME;
			if (win->isInsideResumeButtom(xMouse, yMouse, infos))
				isPaused = false;
			infos = QUIT;
			if (win->isInsideResumeButtom(xMouse, yMouse, infos))
			{
				quit = true;
			}
		}
		//printf("mouse click %d\n", event.button.button);
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
	if (key == SDL_SCANCODE_P)
		isPaused = !isPaused;
	if (key == SDL_SCANCODE_ESCAPE)
	{
		printf("escape");
		return true;
	}

	if (IAMode)
		return false; // pour empecher les touches de changer qqchose
	switch (key)
	{
	case SDL_SCANCODE_A:
	case SDL_SCANCODE_LEFT:
		direction = LEFT;
		break;
	case SDL_SCANCODE_D:
	case SDL_SCANCODE_RIGHT:
		direction = RIGHT;
		break;
	case SDL_SCANCODE_UP:
		direction = ROT_R;
		break;
	case SDL_SCANCODE_W:
		direction = ROT_L;
		break;
	case SDL_SCANCODE_S:
	case SDL_SCANCODE_DOWN:
		direction = DOWN;
		break;
	case SDL_SCANCODE_SPACE:
		direction = FAR_DOWN;
		break;
	case SDL_SCANCODE_C:
		board->changePiece();
		break;
	default:
		break;
	}
	return quit;
}

bool Game::update()
{
	int nbLines;
	if(!IAMode)
		board->update_direction(direction);
	if (board->IsGameOver())
		return true;

	if (!IAMode && !board->DetectCollision())
		board->moveCurrentPiece();
	/*else if (board->DetectCollision() == 2)
	{
		board->getCurrentPiece()->set_finished();
		board->print_piece_to_background(); // print la pièce dans le background avant de générer la suivante
		nbLines = board->LineFull();					//Efface les lignes pleines
		board->UpdateLevel();
		board->setScore(board->computeScore(nbLines));
		board->nbHold = 0;
		board->update_screenNextPieces();
		piece = board->currentPiece;
	}*/
	else if (board->DetectCollision() == 2)
	{
		int now = SDL_GetTicks();
		int aBouge = 1;
		int intervalle = 1000 / (1 + (board->get_level() + 1) / 15);
		//timer_fixation = SDL_AddTimer(intervalle, update_timer_fixation_callback, &aBouge);
		//while (SDL_GetTicks() - now < 4 * intervalle && timer_fixation)
		if (!board->getCurrentPiece()->getStateFinished())
		{
			while (SDL_GetTicks() - now < 4 * intervalle && aBouge != 0)
			{
				SDL_Event event;
				if (SDL_PollEvent(&event))
				{
					check_event(event);
					if (!IAMode)
					{
						board->update_direction(direction);
						if (direction == NO_MOVE)
						{
							aBouge = 0;
						}
						else if (!board->DetectCollision())
						{
							aBouge = 1;
							board->moveCurrentPiece();
							win->render(planche->get_surf(), board, false, false);
							board->print_piece_to_board();
							board->print_projection();
						}
					}
				}
			}
		}
		//SDL_RemoveTimer(timer_fixation);
		board->getCurrentPiece()->set_finished();
		board->print_piece_to_background(); // print la pièce dans le background avant de générer la suivante
		nbLines = board->LineFull();					//Efface les lignes pleines
		board->UpdateLevel();
		board->setScore(board->computeScore(nbLines));
		board->nbHold = 0;
		board->update_screenNextPieces();
		piece = board->currentPiece;
	}
	return false;
}

Uint32 Game::update_timer_fixation_callback(Uint32 intervalle, void* parametre)
{
	int * aBouge = static_cast<int*>(parametre);
	if (*aBouge != 0)
	{
		*aBouge = 0;
		return intervalle;
	}
	return 0;
}

Uint32 Game::update_timer_descente_callback(Uint32 intervalle, void *parametre)
{
	Board *myboard = static_cast<Board *>(parametre);
	if (!isPaused && !menuMode)
	{
		myboard->update_direction(DOWN);
		if (!myboard->DetectCollision())
		{
			myboard->moveCurrentPiece();
		}
	}
	return (1000 / (1 + (myboard->get_level() + 1) / 15));
}

void Game::loop()
{
	int prev = 0, now = 0;
	bool quit = false;

	timer_descente = SDL_AddTimer(1000, update_timer_descente_callback, board); /* faire descendre la piece toutes les secondes*/

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
			if(!IAMode)
				reset_key(); //direction NOMOVE
		}
		if (now - prev > 50) // timer pour le FPS
		{
			if (!isPaused && !menuMode && !IAMode)
			{
				quit = update();
				win->render(planche->get_surf(), board, false, false);
				board->print_piece_to_board();
				board->print_projection();
			}
			else if (isPaused && !menuMode)
			{
				win->render(planche->get_surf(), board, true, false);
			}
			else if (menuMode)
				win->render(planche->get_surf(), board, false, true);
			else if (IAMode)
			{
				IAPlayer->chkAllCombinaison();
				win->render(planche->get_surf(), board, false, false);
				board->print_piece_to_board();
				board->print_projection();
				SDL_Delay(500);
			}
			prev = now;
		}
	}

	SDL_DestroyWindow(win->get_w());
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
