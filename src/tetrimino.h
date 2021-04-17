#ifndef _TETRIMINO_
#define _TETRIMINO_
using namespace std;
#include <iostream>
#include <SDL.h>
#include <vector>

#define TETR_SIZE 20

typedef enum tetrimino_type
{
    BARRE,  // cyan
    BLOC,   //jaune
    T_TYPE, //violet
    L_TYPE,
    J_TYPE,
    Z_TYPE,
    S_TYPE
} tetrimino_type;

// Used in the Window_surface ==> more convenient
// but transform in SDL_Color afterward
typedef enum color_type
{
    CYAN,
    YELLOW,
    PURPLE,
    ORANGE,
    BLUE,
    RED,
    GREEN
} color_type;

typedef enum MOV_DIRECTION
{
    LEFT,
    RIGHT,
    DOWN,
    ROT_R,
    ROT_L,
    NO_MOVE,
    FAR_DOWN
} MOV_DIRECTION;

class Tetrimino
{
protected:

    /***
 * matrix2 : a matrix containing all the tetriminos and their 4 roations
 *              each tetrimino has a number (1 to 7) representing its color
 * tetr_wallkick : a matrix representing the possibilities a tetrimino has when 
 *                  it wants to rotate (following the Super Rotation System)
 * color : color for the tetriminos
 * type_t : type of the tetrimino (barre, bloc, etc...)
 * num_rot : number of the actual rotation state of the piece (0 to 3)
 * shape : shape of the tetriminos
 * finished : a bool stating if the piece is immobile (true) or still moving (false)
 * ***/

    static vector<vector<vector<vector<int>>>> matrix2; 
    static vector<vector<vector<vector<int>>>> tetr_wallkick;
    SDL_Color *color;
    tetrimino_type type_t;
    int num_rot;
    SDL_Rect *shape;
    bool finished; 

public:

    /***
 * size : SERT A RIEN
 * current_tetr : the current tetrimino shape and rotation state
 * x, y : positions of the tetrimino
 * ***/
    int size;
    vector<vector<int>> current_tetr;
    int x, y;

    /***
 * tetrimino constructor and destructor
 * ***/
    Tetrimino(int x_, int y_, int size_, tetrimino_type type_t_);
    ~Tetrimino();

    /***
 * SERT A RIEN
 * ***/
    void print_tetrimino();

   /***
 * rotate the tetrimino according to the direction_ (left or right rotation)
 * does not look if the rotation is possible or not, it is the function
 * TryRotate() in the board class that does it
 * ***/
    void rotate(MOV_DIRECTION direction_);

    /***
 * return the type of the tetrimino (barre, bloc, etc...)
 * ***/
    tetrimino_type get_type();

    /***
 * return the rotation number (state) of the current tetrimino
 * ***/
    int get_num_rot();

    /***
 * return the matrix tetr_wallkick seen before
 * ***/
    vector<vector<vector<vector<int>>>> get_wallkick();

    /***
 * change the coordinates of the current tetrimino
 * ***/
    void set_coord(int x_, int y_); // si -1 on touche pas à la coord
                                          /**
     * On utilise toujours les coordonnes x et y de la classe et pas ceux de shape, 
     * les coord de shapes sont actualisées à chaque draw
    **/

    /***
 * set the state of the piece as "finished" (called when the piece is landed)
 * ***/
    void set_finished();

    /***
 * return true if the state is "finished" (the piece is immobile) or false if not
 * ***/
    bool getStateFinished();

    /***
 * SERT A RIEN
 * ***/
    void print_coord();
};

#endif