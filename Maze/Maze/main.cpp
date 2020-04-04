#include "ControlFunction.h"

//=============================== MAIN =============================== //
//Nitzan Rahom 312496425
//Yair Dana 305789596

/*Welcome To our Maze Game
Choose 1 to Make Your Own Maze
choose 2 to Make a Random Maze

Enter a ROW & COL Number, those numbers will be the Height and Width Of the Maze.
Row - up to 80 rows
Col - Up to 25 cols
*For Random Maze you should choose a Odd numbers

IF YOU CHOOSE (1) -YOUR OWN MAZE:
The frame of the Maze except the entrance/exit point should be '*'
For the a vaild Maze you can enter only '*' or blank space ' '
Entrance in the Maze will be point (1,0) - BLANK
Exit in the Maze will be point (Row-2, Col-1) - BLANK

Wrong inputs will get you out of the program.
HAVE FUN!
*/
int main()
{
	Maze* maze = runMakeMaze();
	maze->checkIfVaildMaze();
	maze->SolveTheMaze();
	delete (maze);
	system("pause");
}



