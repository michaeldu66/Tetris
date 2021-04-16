// rayanlegris@gmail.com
#include "game.h"

bool Game::isPaused; // car variable static pour l'utiliser dans le callback
bool Game::menuMode; // car variable static pour l'utiliser dans le callback
bool Game::IAMode;

void Game::init()
{
	win = new WindowSurface(false);
	planche = new Sprite("src/sprites.bmp");
	Player_board = new Board(10);
	IA_board = new Board(10 + WIN_W/TETR_SIZE);//+WIN_W
	piece = Player_board->getCurrentPiece();
	direction = NO_MOVE;
	Player_board->print_piece_to_next();
	isPaused = false;

	music = Mix_LoadMUS("tetrisSong.mp3");
	if (!music)
		printf("Mix_LoadMUS(\"music.mp3\"): %s\n", Mix_GetError());
	//Mix_PlayMusic(music, -1);
	menuMode = true;

	IAPlayer = new virtualPlayer(IA_board);
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
			{
				//delete IA_board;
				//delete IAPlayer;
				IA_board = nullptr;
				menuMode = false;
			}
			infos = IA;
			if (win->isInsideResumeButtom(xMouse, yMouse, infos))
			{
				menuMode = false;
				IAMode = true;
				win->ResizeWindow(win->get_w());
				IA_board->print_piece_to_next();
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

	//if (IAMode)
		//return false; // pour empecher les touches de changer qqchose
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
		Player_board->changePiece();
		break;
	default:
		break;
	}
	return quit;
}

bool Game::IsGameOver(Board* board_)
{
	if (board_ != nullptr)
	{
		if (board_->get_IsOut() == true)
		{
			return true;
		}
	}
	return false;
}

/*bool Game::update(Board * board_)
{
	if (board_ == nullptr)
	{
		return false;
	}
	int nbLines;
	//Player_board->update_direction(direction);
	//if(board_ != IA_board)
	//	board_->update_direction(direction);
	if (IsGameOver(board_))
	{
		printf("GAME OVER\n");
		return true;
	}
	

	if (board_ != IA_board && !board_->DetectCollision())
		board_->moveCurrentPiece();
	//if (!Player_board->DetectCollision())
	//	Player_board->moveCurrentPiece();

	else if (board_->DetectCollision() == 2)
	{
		if (!board_->getCurrentPiece()->getStateFinished())
		{
			int now = SDL_GetTicks();
			int aBouge = 1;
			int intervalle = 1000 / (1 + (board_->get_level() + 1) / 15);
			while (SDL_GetTicks() - now < 4 * intervalle && aBouge != 0)
			{
				aBouge = 0;
				//board->update_direction(NO_MOVE);
				SDL_Event event;
				if (SDL_PollEvent(&event))
				{
					aBouge = 1;
					check_event(event);
					//if (!IAMode)
					reset_key();
					//if (!IAMode)
					//{
					board_->update_direction(direction);
					if (!board_->DetectCollision())
					{
						aBouge = 1;
						board_->moveCurrentPiece();
						win->render(planche->get_surf(), board_, nullptr, false, false, false);
						board_->print_piece_to_board();
						board_->print_projection();
					}
					//}
				}
			}
		}
		//SDL_RemoveTimer(timer_fixation);
		//board->getCurrentPiece()->set_finished();
		board_->GoFarDown();
		board_->print_piece_to_background(); // print la pièce dans le background avant de générer la suivante
		nbLines = board_->LineFull();					//Efface les lignes pleines
		board_->UpdateLevel();
		board_->setScore(board_->computeScore(nbLines));
		board_->set_nbHold(0);
		board_->update_screenNextPieces();
		piece = board_->currentPiece;
	}
	return false;
}*/

/*bool Game::update(Board* Playerboard_, Board * IAboard_)
{
	int nbLines;
	Playerboard_->update_direction(Player_board->direction);
	if (IsGameOver(Playerboard_) == true || IsGameOver(IAboard_) == true);
	{
		printf("GAME OVER\n");
		return true;
	}

		if (!Playerboard_->DetectCollision())
			Playerboard_->moveCurrentPiece();

		if (Playerboard_->DetectCollision() == 2)
		{
			if (!Playerboard_->getCurrentPiece()->getStateFinished())
			{
				int now = SDL_GetTicks();
				int aBouge = 1;
				int intervalle = 1000 / (1 + (Playerboard_->get_level() + 1) / 15);
				while (SDL_GetTicks() - now < 4 * intervalle && aBouge != 0)
				{
					aBouge = 0;
					//board->update_direction(NO_MOVE);
					SDL_Event event;
					if (SDL_PollEvent(&event))
					{
						aBouge = 1;
						check_event(event);
						//if (!IAMode)
						reset_key();
						//if (!IAMode)
						//{
						Playerboard_->update_direction(direction);
						if (!Playerboard_->DetectCollision())
						{
							aBouge = 1;
							Playerboard_->moveCurrentPiece();
							win->render(planche->get_surf(), Playerboard_, IAboard_, false, false, false);
							Playerboard_->print_piece_to_board();
							Playerboard_->print_projection();
						}
						//}
					}
				}
			}
			//SDL_RemoveTimer(timer_fixation);
			//board->getCurrentPiece()->set_finished();
			Playerboard_->GoFarDown();
			Playerboard_->print_piece_to_background(); // print la pièce dans le background avant de générer la suivante
			nbLines = Playerboard_->LineFull();					//Efface les lignes pleines
			Playerboard_->UpdateLevel();
			Playerboard_->setScore(Playerboard_->computeScore(nbLines));
			Playerboard_->set_nbHold(0);
			Playerboard_->update_screenNextPieces();
			//piece = board_->currentPiece;
		}
		if (IAboard_ != nullptr) 
		{
			if (IAboard_->DetectCollision() == 2)
			{
				IAboard_->GoFarDown();
				IAboard_->print_piece_to_background(); // print la pièce dans le background avant de générer la suivante
				nbLines = IAboard_->LineFull();					//Efface les lignes pleines
				IAboard_->UpdateLevel();
				IAboard_->setScore(IAboard_->computeScore(nbLines));
				IAboard_->set_nbHold(0);
				IAboard_->update_screenNextPieces();
				//piece = board_->currentPiece;
			}
	}
	return false;
}*/

bool Game::update()
{
	int nbLines;
	Player_board->update_direction(direction);
	if (IsGameOver(Player_board) == true || IsGameOver(IA_board) == true)
	{
		printf("GAME OVER\n");
		return true;
	}

	if (!Player_board->DetectCollision())
		Player_board->moveCurrentPiece();

	if (Player_board->DetectCollision() == 2)
	{
		if (!Player_board->getCurrentPiece()->getStateFinished())
		{
			int now = SDL_GetTicks();
			int aBouge = 1;
			int intervalle = 1000 / (1 + (Player_board->get_level() + 1) / 15);
			while (SDL_GetTicks() - now < 4 * intervalle && aBouge != 0)
			{
				reset_key();
				if (SDL_GetTicks() - now > intervalle)
				{
					aBouge = 0;
				}
				//board->update_direction(NO_MOVE);
				SDL_Event event;
				if (SDL_PollEvent(&event))
				{
					//aBouge = 1;
					check_event(event);
					Player_board->update_direction(direction);
					if (!Player_board->DetectCollision())
					{
						aBouge = 1;
						Player_board->moveCurrentPiece();
						win->render(planche->get_surf(), Player_board, IA_board, false, false);
						Player_board->print_piece_to_board();
						Player_board->print_projection();
					}
				}
			}
		}
		//board->getCurrentPiece()->set_finished();
		Player_board->GoFarDown();
		Player_board->print_piece_to_background(); // print la pièce dans le background avant de générer la suivante
		nbLines = Player_board->LineFull();					//Efface les lignes pleines
		Player_board->UpdateLevel();
		Player_board->setScore(Player_board->computeScore(nbLines));
		Player_board->set_nbHold(0);
		Player_board->update_screenNextPieces();
	}
	if (IA_board != nullptr)
	{
		if (IA_board->DetectCollision() == 2)
		{
			IA_board->GoFarDown();
			IA_board->print_piece_to_background(); // print la pièce dans le background avant de générer la suivante
			nbLines = IA_board->LineFull();					//Efface les lignes pleines
			IA_board->UpdateLevel();
			IA_board->setScore(IA_board->computeScore(nbLines));
			IA_board->set_nbHold(0);
			IA_board->update_screenNextPieces();
		}
	}
	return false;
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

	timer_descente_Player = SDL_AddTimer(1000, update_timer_descente_callback, Player_board); /* faire descendre la piece toutes les secondes*/

	//while (quit_Player == false && quit_IA == false)
	while (quit == false)
	{
		now = SDL_GetTicks();
		//update();
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			if (check_event(event))
				break;
			if (!isPaused)
			{
				update();
			}
				reset_key(); //direction NOMOVE
		}
		if (now - prev > 50) // timer pour le FPS
		{
			if (!isPaused && !menuMode) // Partie où on update le Player_board et l'IA_board
			{
				if (IA_board == nullptr) 
				{
					quit = update();

					win->render(planche->get_surf(), Player_board, IA_board, false, false);
					Player_board->print_piece_to_board();
					Player_board->print_projection();
				}
				else
				{
					quit = update();
					win->render(planche->get_surf(), Player_board, IA_board, false, false);
					Player_board->print_piece_to_board();
					Player_board->print_projection();
					IA_board->print_piece_to_board();
					IAPlayer->chkAllCombinaison();
					//SDL_Delay(1000 / (1 + (IA_board->get_level() + 1) / 15));
				}
				/*quit_Player = update(Player_board);
				win->render(planche->get_surf(), Player_board, IA_board, false, false, false);
				Player_board->print_piece_to_board();
				Player_board->print_projection();

				if (IA_board != nullptr)
				{
					//printf("IA");
					quit_IA = update(IA_board);
					win->render(planche->get_surf(), Player_board, IA_board, false, false, true);
					IA_board->print_piece_to_board();
					IAPlayer->chkAllCombinaison();
					SDL_Delay(1000 / (1 + (IA_board->get_level() + 1) / 15));
				}*/
			}
			else if (isPaused && !menuMode)
			{
					win->render(planche->get_surf(), Player_board, IA_board, true, false);
			}
			else if (menuMode)
			{
				win->render(planche->get_surf(), Player_board, IA_board, false, true);
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
