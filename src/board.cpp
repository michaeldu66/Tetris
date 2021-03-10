#include "board.h"
Board::Board()
{
	carre_grill = new SDL_Rect();
	carre_grill->h = TETR_SIZE;
	carre_grill->w = TETR_SIZE;

	screenWithBlock.resize(BOARD_HEIGHT);  // Allocation des vectors
	screenBackground.resize(BOARD_HEIGHT); // Allocation des vectors
	//screenIABackground.resize(BOARD_HEIGHT); // Allocation des vectors
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		screenBackground[i].resize(BOARD_WIDTH);
		screenWithBlock[i].resize(BOARD_WIDTH);
		//screenIABackground[i].resize(BOARD_WIDTH);
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			screenBackground[i][j] = FREE;
			screenWithBlock[i][j] = FREE;
		}
	}

	currentPiece = GenerateRandomShape();
	direction = NO_MOVE;

	for (int i = 0; i < 8; i++)
	{
		color[i] = new SDL_Color();
		switch (i)
		{
		case 0:
			color[i]->r = 0;
			color[i]->g = 0;
			color[i]->b = 0;
			break;

		case 1:
			color[i]->r = 0;
			color[i]->g = 255;
			color[i]->b = 255;
			break;

		case 2:
			color[i]->r = 255;
			color[i]->g = 255;
			color[i]->b = 0;
			break;

		case 3:
			color[i]->r = 255;
			color[i]->g = 0;
			color[i]->b = 255;
			break;

		case 4:
			color[i]->r = 255;
			color[i]->g = 165;
			color[i]->b = 0;
			break;

		case 5:
			color[i]->r = 0;
			color[i]->g = 0;
			color[i]->b = 255;
			break;

		case 6:
			color[i]->r = 255;
			color[i]->g = 0;
			color[i]->b = 0;
			break;

		case 7:
			color[i]->r = 0;
			color[i]->g = 255;
			color[i]->b = 0;
			break;
		}
	}

	totalScore = 0;
	totalLines = 0;
	police = TTF_OpenFont("src/GUNSHIP2.TTF", 20);
	colorPolice = {74, 69, 68};
	positionInfos = new SDL_Rect();
	cout << "BOARD constructor" << endl;
}

void Board::setCurrentPiece(Tetrimino *tetr)
{
	currentPiece = tetr;
}

Tetrimino *Board::getCurrentPiece()
{
	return currentPiece;
}

void Board::update_direction(MOV_DIRECTION direction_)
{
	direction = direction_;
	//cout << "direction set to " << direction << endl;
}

void Board::moveCurrentPiece()
{
	switch (direction)
	{
	case LEFT:
		currentPiece->x--;
		break;
	case RIGHT:
		currentPiece->x++;
		break;
	case DOWN:
		currentPiece->y++;
		break;
	case UP:
		currentPiece->rotate();
		break;
	case FAR_DOWN:
		GoFarDown();
		break;
	case NO_MOVE:
		//cout << "on bouge pas la piece" << endl;
		break;
	}
}

void Board::moveBackCurrentPiece()
{
	switch (direction)
	{
	case LEFT:
		currentPiece->x++;
		break;
	case RIGHT:
		currentPiece->x--;
		break;
	case DOWN:
		currentPiece->y--;
		break;
	case UP:
		currentPiece->rotate();
		currentPiece->rotate();
		currentPiece->rotate();
		break;
	}
}

void Board::print_board()
{
	cout << "affichage du background board" << endl;
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			cout << screenBackground[i][j];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Board::draw_board(SDL_Renderer *rend)
{
	//print_board();
	int nb_color = -1;
	for (int i = 0; i < BOARD_HEIGHT; i++) //centrée en hauteur
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			carre_grill->x = (ORIGIN_X + j) * TETR_SIZE;
			carre_grill->y = (ORIGIN_Y + i) * TETR_SIZE;
			nb_color = screenWithBlock[i][j];
			SDL_SetRenderDrawColor(rend, color[nb_color]->r, color[nb_color]->g, color[nb_color]->b, 255); // inside of squares black
			SDL_RenderFillRect(rend, carre_grill);
			SDL_SetRenderDrawColor(rend, 75, 75, 75, 0);
			SDL_RenderDrawRect(rend, carre_grill); //borderline of squares (in white)
		}
	}
}

void Board::print_piece_to_board()
{
	refresh_screen();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (currentPiece->current_tetr[i][j])
				screenWithBlock[currentPiece->y - ORIGIN_Y + i][currentPiece->x - ORIGIN_X + j] = currentPiece->current_tetr[i][j];
		}
	}
}

//Pour l'IA
void Board::deletePieceFromBackground()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (currentPiece->current_tetr[i][j])
				screenBackground[currentPiece->y - ORIGIN_Y + i][currentPiece->x - ORIGIN_X + j] = 0;
		}
	}
}

//Affiche les pièces sur le background pour qu'elles restent visibles
void Board::print_piece_to_background()
{
	//refresh_screen();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (currentPiece->current_tetr[i][j])
				screenBackground[currentPiece->y - ORIGIN_Y + i][currentPiece->x - ORIGIN_X + j] = currentPiece->current_tetr[i][j];
		}
	}
}

void Board::refresh_screen()
{
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (screenBackground[i][j] != screenWithBlock[i][j])
				screenWithBlock[i][j] = screenBackground[i][j];
		}
	}
	//screenIABackground.assign(screenBackground.begin(), screenBackground.end());
}

int Board::DetectCollision()
{
	int detected = 0;

	if (direction == UP)
		return TryRotate();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (currentPiece->current_tetr[i][j])
			{
				switch (direction)
				{
				case LEFT:
					if (LookLeft(i, j))
						detected = 1;
					break;
				case RIGHT:
					if (LookRight(i, j))
						detected = 1;
					break;
				case DOWN:
					if (LookDown(i, j))
						detected = 1;
					break;
				case NO_MOVE:
					if (LookDown(i, j))
						detected = 1;
					break;
				default:
					break;
				}
			}
		}
	}

	return detected;
}

// Regarde juste en-dessous de la pièce s'il y en a une autre ou le bord
int Board::LookDown(int idy, int idx)
{
	int val_y = currentPiece->y - ORIGIN_Y + idy + 1;
	if (val_y < 20) // pour le bord
	{
		if (screenBackground[val_y][currentPiece->x - ORIGIN_X + idx] != 0) // ligne juste en dessous
		{
			currentPiece->set_finished();
			return 1;
		}
		return 0;
	}
	currentPiece->set_finished();
	return 1;
}

// Pour l'IA : Regarde juste au-dessus de la pièce s'il y en a une autre ou le bord
int Board::LookUp(int idy, int idx)
{
	int val_y = currentPiece->y - ORIGIN_Y + idy - 1;
	if (val_y >= 0) // pour le bord
	{
		if (screenBackground[val_y][currentPiece->x - ORIGIN_X + idx] != 0) // ligne juste en dessous
		{
			return 1;
		}
		return 0;
	}
	return 1;
}

// Regarde juste à droite de la pièce s'il y en a une autre ou le bord
int Board::LookRight(int idy, int idx)
{
	int val_x = currentPiece->x - ORIGIN_X + idx + 1;
	if (val_x < 10)
	{
		if (screenBackground[currentPiece->y - ORIGIN_Y + idy][val_x] != 0)
		{
			return 1;
		}
		return 0;
	}
	return 1;
}

// Regarde juste à gauche de la pièce s'il y en a une autre ou le bord
int Board::LookLeft(int idy, int idx)
{
	int val_x = currentPiece->x - ORIGIN_X + idx - 1;
	if (val_x > -1)
	{
		if (screenBackground[currentPiece->y - ORIGIN_Y + idy][val_x] != 0)
		{
			return 1;
		}
		return 0;
	}
	return 1;
}
/***
 * Essaye de tourner la pièce et regarde si ça ne dépasse pas du board ou sur une autre pièce 
 * fonctionne mais pour quand c'est proche d'une pièce voisine faut prendre en compte
 * le timer genre laisser un délai avec une confition if (blabla && timer >1sec)
 * A rajouter plus tard pck pour l'instant flemme * 
 * ***/

int Board::TryRotate()
{
	moveCurrentPiece();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (currentPiece->current_tetr[i][j])
			{
				if (currentPiece->x - ORIGIN_X + j < 0 || currentPiece->x - ORIGIN_X + j > 9 || currentPiece->y - ORIGIN_Y + i > 19)
				{
					moveBackCurrentPiece();
					return 1;
				}
				else if (screenBackground[currentPiece->y - ORIGIN_Y + i][currentPiece->x - ORIGIN_X + j] != 0)
				{
					moveBackCurrentPiece();
					return 1;
				}
			}
		}
	}
	moveBackCurrentPiece();
	return 0;
}

bool Board::IsGameOver()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		if (screenBackground[0][i] != 0)
			return true;
	}
	return false;
}

// Permet de descendre une pièce le plus bas possible en ligne droite grçace à la touche espace
void Board::GoFarDown()
{
	int detected = 0;
	while (detected == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (currentPiece->current_tetr[i][j])
				{
					if (LookDown(i, j))
					{
						detected = 1;
					}
				}
			}
		}
		if (detected == 0)
			currentPiece->y++;
	}
}

// Pour l'IA
void Board::GoFarUp()
{
	int detected = 0;
	int aBouger = 0;
	int val_y;
	while (detected == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				val_y = currentPiece->y - ORIGIN_Y + i - 1;
				if (val_y < 0)
				{
					detected = 1;
					break;
				}
				if (currentPiece->current_tetr[i][j])
				{
					if (LookUp(i, j))
						detected = 1;
				}
			}
		}
		if (detected == 0)
		{
			currentPiece->y--;
			aBouger = 1;
		}
	}
	if (aBouger)
		printf(" a bouger\n");
}

/***
 * Fonctionnel MAIS il y a un cas qui bug, genre si il y a eu plusieurs fois des 
 * lignes full qui ont disparus bah des fois ya des vides entre deux carrés
 * donc faudrait faire une fonction "delete holes"  qui 
 * enlève les trous que la gravité ne permettent, cf le screen que je t'ai envoyé. 
 * ***/
int Board::LineFull()
{
	int full;
	int nbLines = 0;

	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		full = 1;
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (screenBackground[i][j] == 0)
			{
				full = 0;
			}
		}
		if (full == 1)
		{
			cout << "on a une line full la numero : " << i << endl;
			nbLines++;
			BringDownColumns(i);
		}
	}
	totalLines += nbLines;
	return nbLines;
}
/***
 * Bring Down Colums for the Row with index i_row 
 * (used when Line Full is used)
 * **/
void Board::BringDownColumns(int i_row)
{
	int i = i_row;
	for (int j = 0; j < BOARD_WIDTH; j++)
	{
		while (i > 0)
		{
			screenBackground[i][j] = screenBackground[i - 1][j];
			i--;
		}
		screenBackground[0][j] = 0;
		i = i_row;
	}
}

/***
 * Pour L'IA, ne descend pas les lignes pleines
 * ***/
int Board::nbLineFull()
{
	int full;
	int nbLines = 0;
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		full = 1;
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (screenBackground[i][j] == 0)
				full = 0;
		}
		if (full == 1)
			nbLines++;
	}
	return nbLines;
}

tetrimino_type Board::GetRandomShape()
{
	srand(time(NULL));
	int Shape = rand() % 7;
	cout << "the random Shape is : " << Shape << endl;
	switch (Shape)
	{
	case 0:
		return BARRE;
	case 1:
		return BLOC;
	case 2:
		return T_TYPE;
	case 3:
		return L_TYPE;
	case 4:
		return J_TYPE;
	case 5:
		return Z_TYPE;
	case 6:
		return S_TYPE;
	}
	return BARRE;
}

Tetrimino *Board::GenerateRandomShape()
{
	Tetrimino *randomTetrimino;
	tetrimino_type randomShape = GetRandomShape();
	if (randomShape == BARRE)
		randomTetrimino = new Tetrimino(14, 6, 4, randomShape); //, randomColor);
	else if (randomShape == BLOC)
		randomTetrimino = new Tetrimino(14, 6, 2, randomShape); // , randomColor);
	else
		randomTetrimino = new Tetrimino(14, 6, 3, randomShape); // , randomColor);
	currentPiece = randomTetrimino;
	return randomTetrimino;
}

/***
 * Compute the score of the Current PIece 
 * (depending of the lines it fills and its y position)
 * 
 * This function is called after the piece is in place
 * and before the new one is generated
 * ***/

int Board::computeScore(int nbLines)
{
	int valYPiece = currentPiece->y - ORIGIN_Y + 1;
	int score = valYPiece * 2;
	switch (nbLines)
	{
	case 1:
		score += 100;
		break;
	case 2:
		score += 300;
		break;
	case 3:
		score += 500;
		break;
	case 4:
		score += 1200;
		break;
	default:
		break;
	}
	return score;
}

void Board::setScore(int valueToAdd)
{
	this->totalScore += valueToAdd;
}

int Board::get_score()
{
	return totalScore;
}

void Board::setPositionInfos(optionInfo infos)
{
	positionInfos->w = (BOARD_WIDTH * TETR_SIZE) / 2;
	positionInfos->h = 3 * TETR_SIZE;
	positionInfos->x = (ORIGIN_X * 30) / 4;
	switch (infos)
	{
	case SCORE:
		positionInfos->y = (BOARD_HEIGHT + 3) * TETR_SIZE;
		break;
	case LINES:
		positionInfos->y = (BOARD_HEIGHT)*TETR_SIZE;
		break;
	}
}
/***
 *Ecris le texte d'affichage de l'option dans un buffer 
 ***/
void Board::textInfos(optionInfo infos)
{
	switch (infos)
	{
	case SCORE:
		snprintf(infosMsg, 100, "Score : %i", totalScore);
		break;
	case LINES:
		snprintf(infosMsg, 100, "Lines : %i", totalLines);
		break;
	}
	infosMsg[strlen(infosMsg)] = '\0';
}
/***
 * Affiche les options (Score et lines faites pour l'instant)
 * sur l'écran avec une police d'écriture toussa
 * ***/
void Board::printInfosToScreen(SDL_Renderer *rend)
{
	for (optionInfo infos = SCORE; infos < 2; infos = optionInfo(int(infos) + 1))
	{
		textInfos(infos);
		textSurface = TTF_RenderText_Solid(police, infosMsg, colorPolice);
		setPositionInfos(infos);
		textTexture = SDL_CreateTextureFromSurface(rend, textSurface);

		SDL_SetRenderDrawColor(rend, 213, 213, 213, 255); // background of text
		SDL_RenderFillRect(rend, positionInfos);
		SDL_RenderDrawRect(rend, positionInfos);

		SDL_RenderCopy(rend, textTexture, NULL, positionInfos);
	}
}

void Board::freeScoreText()
{
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

/****
 * fonction qui compte les trous
 * ***/

int Board::getNbHoles()
{
	bool startPiece = false;
	int cptHoles = 0;
	for (int j = 0; j < BOARD_WIDTH; j++)
	{
		for (int i = 0; i < BOARD_HEIGHT; i++)
		{
			if (!startPiece && screenBackground[i][j] != 0)
				startPiece = true;

			if (startPiece && screenBackground[i][j] == 0)
				cptHoles++;
		}
		startPiece = false;
	}
	return cptHoles;
}