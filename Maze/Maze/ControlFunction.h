#ifndef _CONTROL_FUNCTION_H
#define _CONTROL_FUNCTION_H

#include "Maze.h"
#include "Point.h"
#include "Stack.h"
#include <string.h>
using namespace std;

//=============================== DECLERTAION FOR FUNCTION =============================== //

//MAIN FUNCTIONS
Maze* runMakeMaze();
Maze* randomMaze();
Maze* makeYourOwnMaze();

//HELPER FUNCTIONS
static void InputRowAndCol(int& row, int& col);
static bool IsVaildInputs(int& col, int& row);

#endif // _CONTROL_FUNCTION_H