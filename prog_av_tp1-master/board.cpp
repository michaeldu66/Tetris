#include "board.h"
Board::Board()
{
	carre_grill = new SDL_Rect();
	carre_grill->h = TETR_SIZE;
	carre_grill->w = TETR_SIZE;

	screenWithBlock.resize(BOARD_HEIGHT);  // Allocation des vectors
	screenBackground.resize(BOARD_HEIGHT); // Allocation des vectors
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		screenBackground[i].resize(BOARD_WIDTH);
		screenWithBlock[i].resize(BOARD_WIDTH);
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
}

// // si les matrices de tetris sont full 0 on delete, fct à faire
// //quand piece bouge plus, on update le background

/*int Board::DetectCollision()
{
	moveCurrentPiece();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (currentPiece->current_tetr[i][j])
			{
				if (OutOfGrillLeft(currentPiece->x, j) ||
					OutOfGrillRight(currentPiece->x, j))
				{
					cout << "Detection Side Detected" << endl;
					moveBackCurrentPiece();
					return 1;
				}
				else if (OutOfGrillDown(currentPiece->y, i))
				{
					cout << "Detection Down Detected" << endl;
					cout << " le state est " << currentPiece->getStateFinished() << endl;
					moveBackCurrentPiece();
					return 1;
				}
			}
		}
	}
	moveBackCurrentPiece();
	return 0;
}*/

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

	// switch (direction)
	// {
	// case LEFT:
	// 	for (int i = 0; i < 4; i++)
	// 	{
	// 		for (int j = 0; j < 4; j++)
	// 		{
	// 			if (currentPiece->current_tetr[i][j])
	// 			{
	// 				if (LookLeft(i, j))
	// 				{
	// 					detected = 1;
	// 				}
	// 			}
	// 		}
	// 	}
	// 	break;

	// case RIGHT:
	// 	for (int i = 0; i < 4; i++)
	// 	{
	// 		for (int j = 0; j < 4; j++)
	// 		{
	// 			if (currentPiece->current_tetr[i][j])
	// 			{
	// 				if (currentPiece->current_tetr[i][j])
	// 				{
	// 					if (LookRight(i, j))
	// 					{
	// 						detected = 1;
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// 	break;

	// case DOWN:
	// 	for (int i = 0; i < 4; i++)
	// 	{
	// 		for (int j = 0; j < 4; j++)
	// 		{
	// 			if (currentPiece->current_tetr[i][j])
	// 			{
	// 				if (LookDown(i, j))
	// 				{
	// 					detected = 1;
	// 				}
	// 			}
	// 		}
	// 	}
	// 	break;

	// case UP:
	// 	return TryRotate();
	// 	break;

	// case NO_MOVE:
	// 	for (int i = 0; i < 4; i++)
	// 	{
	// 		for (int j = 0; j < 4; j++)
	// 		{
	// 			if (currentPiece->current_tetr[i][j])
	// 			{
	// 				if (LookDown(i, j))
	// 				{
	// 					detected = 1;
	// 				}
	// 			}
	// 		}
	// 	}
	// 	break;

	// default:
	// 	break;
	// }
	return detected;
}

// Regarde juste en-dessous de la pièce s'il y en a une autre ou le bord
int Board::LookDown(int idy, int idx)
{
	//cout << screenBackground[currentPiece->y - ORIGIN_Y + idy][currentPiece->x - ORIGIN_X + idx] << endl;
	int val_y = currentPiece->y - ORIGIN_Y + idy + 1;
	if (val_y < 20)
	{
		//cout << screenBackground[currentPiece->y - ORIGIN_Y + idy + 1][currentPiece->x - ORIGIN_X + idx] << endl;
		if (screenBackground[val_y][currentPiece->x - ORIGIN_X + idx] != 0)
		{
			currentPiece->set_finished();
			return 1;
		}
		return 0;
	}
	currentPiece->set_finished();
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
		{
			currentPiece->y++;
		}
	}
}

/***
 * Fonctionnel MAIS il y a un cas qui bug, genre si il y a eu plusieurs fois des 
 * lignes full qui ont disparus bah des fois ya des vides entre deux carrés
 * donc faudrait faire une fonction "delete holes"  qui 
 * enlève les trous que la gravité ne permettent, cf le screen que je t'ai envoyé. 
 * ***/
void Board::LineFull()
{
	int full;
	int nb_lines = 0;
	vector<int> linesFull;
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
			nb_lines++;
			BringDownColumns(i);
		}
	}
	switch (nb_lines)
	{
	case 1:
		totalScore += 40;
		break;
	case 2:
		totalScore += 100;
		break;
	case 3:
		totalScore += 300;
		break;
	case 4:
		totalScore += 1200 ;
		 break;
	default:
		break;
	}
	totalLines += nb_lines;
}
/***
 * Bring Down Colums for the Row with index i_row 
 * (used when Line Full is used)
 * **/
/*void Board::BringDownColumns(int i_row)
{
	int idx_up, k;
	for (int j = BOARD_WIDTH - 1; j >= 0; j--)
	{
		if (i_row > 0)
		{
			idx_up = i_row - 1;
			while (screenBackground[idx_up][j] == 0 && idx_up > 0)
				idx_up--;
			k = i_row;
			while (idx_up >= 0)
			{
				screenBackground[k][j] = screenBackground[idx_up][j];
				idx_up--;
				k--;
			}
		}
		else if (i_row == 0)
			screenBackground[i_row][j] = 0;
	}
}*/

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
	//color_type randomColor = GetRandomColor();
	if (randomShape == BARRE)
		randomTetrimino = new Tetrimino(14, 6, 4, randomShape); //, randomColor);
	else if (randomShape == BLOC)
		randomTetrimino = new Tetrimino(14, 6, 2, randomShape); // , randomColor);
	else
		randomTetrimino = new Tetrimino(14, 6, 3, randomShape); // , randomColor);
	currentPiece = randomTetrimino;
	return randomTetrimino;
}
