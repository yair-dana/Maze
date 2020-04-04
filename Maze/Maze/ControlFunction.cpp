#include "ControlFunction.h"

//============================================ MAIN FUNCTIONS ===============================================//
Maze* runMakeMaze()
{
	//The funcion get input from user and open the correct function
	//1- build you own maze, 2- the computer build a random maze
	int digit;
	Maze* tempMaze = nullptr;
	bool flag = false;
	cout << "============= Welcome To Our Maze =============\n";
	cout << "Press (1) to make your Own Maze\nPress (2) to make a Random Maze\n";
	cin >> digit;
	while (!flag)
	{
		if (digit == 1)
		{
			tempMaze = makeYourOwnMaze();
			flag = true;
		}
		else if (digit == 2)
		{
			tempMaze = randomMaze();
			flag = true;
		}
		else
		{
			cout << "The number is invaild\n";
			cin >> digit;
		}
	}

	return tempMaze;
}
//---------------------------------------------------------------------------------------------------//

Maze* makeYourOwnMaze()
{
	//The funcion gets inputs from user and making the Certain Maze 
	char* str;
	int Row, Col;
	int indexRowLine = 0;

	InputRowAndCol(Row, Col); //get input of row and col from user
	Maze* tempMaze = new Maze(Row, Col); //Alloction address of Maze object.

	str = new char[(Maze::MAX_COL_ROW + 1)]; // Allocation for string
	cin.ignore();
	cout << "please enter your Maze " << Row << "X" << Col << endl;
	for (indexRowLine; indexRowLine < Row; indexRowLine++) // Puting in the MAZE each row
	{
		cin.getline(str, Maze::MAX_COL_ROW);
		tempMaze->checkInputAndSetStrInMaze(indexRowLine, str); //putinh the input string inside the maze
	}
	return (tempMaze);
}
//---------------------------------------------------------------------------------------------------//
Maze* randomMaze()
{
	int row, col;
	bool flag = false;
	//cout << "please enter enter the size of the maze, enter the row and then the col" << endl;
	InputRowAndCol(row, col);
	Maze* TempMaze = new Maze(row, col);
	TempMaze->MakeArandomeMaze();
	return (TempMaze);
}
//---------------------------------------------------------------------------------------------------//


//============================================ HELPER FUNCTIONS ===============================================//
static void InputRowAndCol(int& row, int& col)
{
	// The function get row and col from user until the inputs vaild.
	bool flag = false;
	while (flag == false)
	{
		cout << "please enter Row number and then col (not rise above 80) " << endl;
		cin >> row >> col;
		flag = IsVaildInputs(col, row);// Helper function for checking the inputs
		if (flag == false)
			cout << "you have enterd invalid row or col number\nplease try again\n" << endl;
	}

}
//---------------------------------------------------------------------------------------------------//
static bool IsVaildInputs(int& col, int& row)
{
	//The funcion Return if it's good MAZE (col && row<80)
	if (col > 80 || row > 25)
		return false;
	return true;
}
//---------------------------------------------------------------------------------------------------//
