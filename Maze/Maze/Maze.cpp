#include "Maze.h"
//============================================COUNSTACTOR AND DESTRACTOR===============================================//
Maze::Maze(const int row, const int col)
{
	//cout << "CONSTACTOR\n";
	setRow(row);
	setCol(col);
	AllocationEmptyMaze();
}
//---------------------------------------------------------------------------------------------------//

Maze::Maze(const Maze& other) :Row(other.Row), Col(other.Col)
{
	//cout << "COPY\n";
	int IdxRow;

	TheMaze = new char* [Row];
	for (IdxRow = 0; IdxRow < other.Row; IdxRow++)
		TheMaze[IdxRow] = strdup(other.TheMaze[IdxRow]);
}
//---------------------------------------------------------------------------------------------------//

Maze::Maze(Maze&& other) :Row(other.Row), Col(other.Col)
{
	//	cout << "MOVE\n";
	int IdxRow;
	TheMaze = new char* [Row];
	for (IdxRow = 0; IdxRow < other.Row; IdxRow++)
	{
		TheMaze[IdxRow] = other.TheMaze[IdxRow];
		other.TheMaze[IdxRow] = nullptr;
	}
}

//---------------------------------------------------------------------------------------------------//

Maze::~Maze()
{
	//	cout << "DESTRACTOR\n";
	int IdxRow, IdxCol;
	for (IdxRow = 0; IdxRow < this->Row; IdxRow++)
		delete TheMaze[IdxRow];

	delete TheMaze;
}

//============================================PRIAVTE METHODS===============================================//
void Maze::AllocationEmptyMaze()
{
	int idx;
	TheMaze = new char* [this->Row];
	if (!TheMaze) // check allocation
	{
		cout << "Error: Allocation Maze\n";
		exit(1);
	}

	for (idx = 0; idx < this->Row; idx++)
	{
		TheMaze[idx] = new char[this->Col + 1];
		if (!TheMaze[idx]) // check allocation
		{
			cout << "Error: Allocation Maze\n";
			exit(1);
		}
		for (int i = 0; i < Col; i++)
			TheMaze[idx][i] = EMPTY;
		TheMaze[idx][Col] = '\0';

	}
}
//---------------------------------------------------------------------------------------------------//
bool Maze::setRow(const int& Row)
{
	if (Row > 80)
	{
		cout << "Invaild number\n";
		return false;
	}
	this->Row = Row;
	return true;
}
//---------------------------------------------------------------------------------------------------//
bool Maze::setCol(const int& Col)
{
	if (Col > 80)
	{
		cout << "Invaild number\n";
		return false;
	}
	this->Col = Col;
	return true;
}
//---------------------------------------------------------------------------------------------------//


//====================HELPERS FOR RANDOM MAZE METHOD====================//
void Maze::InitiateRandomMaze()
{
	char* tempString = new char[Col + 1];

	//making a string for the EVEN row
	for (int j = 0; j < Col; j++)
		tempString[j] = WALL;
	tempString[Col] = '\0';
	//put the string in the EVEN row
	for (int i = 0; i < Row; i += 2)
		this->checkInputAndSetStrInMaze(i, tempString);

	// making a string for the ODD row
	for (int j = 0, i = 1; j < Col; j += 2, i += 2)
	{
		tempString[j] = WALL;
		if (i < Col)
			tempString[i] = EMPTY;
	}
	tempString[Col] = '\0';
	//put the stirng in the ODD row
	for (int i = 1; i < Row; i += 2)
		this->checkInputAndSetStrInMaze(i, tempString);

	this->setAcertainMazePoint(EMPTY, 1, 0); //entrance;
	this->setAcertainMazePoint(EMPTY, Row - 2, Col - 1);//exit

	delete[] tempString; //Delete dynamic allocaton
}
//---------------------------------------------------------------------------------------------------//
void Maze::checkForNeighboorsAndChooseOne(Point& currVerctor, Point& newNeighboor)
{
	bool foundNeighboorForRand;
	int index;
	int y = currVerctor.getY();
	int x = currVerctor.getX();

	CreatingNeigboorsArray(x, y);
	index = findNeighboorForRand();//while we didnt find a neighboor that exist and withstand our demands. 

	if (index != No_Neigboors)
	{
		if (index == left)
			TheMaze[x][y - 1] = EMPTY;
		if (index == right)
			TheMaze[x][y + 1] = EMPTY;
		if (index == down)
			TheMaze[x + 1][y] = EMPTY;
		if (index == up)
			TheMaze[x - 1][y] = EMPTY;
		newNeighboor.setX(Neighboors[index].getX());
		newNeighboor.setY(Neighboors[index].getY());
	}
	else
	{
		newNeighboor.setX(0); //No_New_Neighboor
		newNeighboor.setY(0); //No_New_Neighboor
	}
}
//---------------------------------------------------------------------------------------------------//
void Maze::CreatingNeigboorsArray(int& x, int& y)
{
	if ((y - 2) > 0)//for left
	{
		if (TheMaze[x][y - 1] == EMPTY)
			if (TheMaze[x][y - 2] == WALL)
			{
				Neighboors[left].setX(x);
				Neighboors[left].setY(y - 2);
			}
	}
	if (x - 2 > 0)//for up
	{
		if (TheMaze[x - 2][y] == EMPTY)
			if (TheMaze[x - 1][y] == WALL)
			{
				Neighboors[up].setX(x - 2);
				Neighboors[up].setY(y);
			}

	}
	if (y + 2 < Col)//for right
	{
		if (TheMaze[x][y + 2] == EMPTY)
			if (TheMaze[x][y + 1] == WALL)
			{
				Neighboors[right].setX(x);
				Neighboors[right].setY(y + 2);
			}
	}

	if (x + 2 < Row)//for down
	{
		if (TheMaze[x + 2][y] == EMPTY)
			if (TheMaze[x + 1][y] == WALL)
			{
				Neighboors[down].setX(x + 2);
				Neighboors[down].setY(y);
			}
	}


}
//---------------------------------------------------------------------------------------------------//
int Maze::findNeighboorForRand()
{
	srand(time(NULL));
	bool DidWeFindAneighboor = false, AreThereAnyNeighboors = false;
	int index;

	// Check the NEIGHBOORS array, if there is a neighboor - AreThereAnyNeighboors=True, else= False
	for (int idx = 0; idx < MAX_NIGHBOORS; idx++)
		AreThereAnyNeighboors |= (Neighboors[idx].getX() != 0 || Neighboors[idx].getY() != 0);

	while (!DidWeFindAneighboor && AreThereAnyNeighboors) //choose the neigboor
	{
		index = rand() % 4;//get index between 0 to 3 
		if ((Neighboors[index].getX() != 0) || (Neighboors[index].getY() != 0))
			DidWeFindAneighboor = true;
	}
	if (DidWeFindAneighboor)
		return  index; //the neigboor that we chose
	else
		return No_Neigboors;
}
//---------------------------------------------------------------------------------------------------//
void Maze::removeNeihboors()
{ //Initiate the array
	for (int i = 0; i < MAX_NIGHBOORS; i++)
	{
		Neighboors[i].setX(0);
		Neighboors[i].setY(0);
	}
}
//---------------------------------------------------------------------------------------------------/
void Maze::cleanTheMaze()
{
	for (int idx_row = 0; idx_row < this->Row; idx_row++)
	{
		for (int idx_col = 0; idx_col < this->Col; idx_col++)
			if (TheMaze[idx_row][idx_col] == VISTED)
				TheMaze[idx_row][idx_col] = EMPTY;
	}
}

//====================HELPERS FOR YOUR OWN MAZE METHOD====================//
void Maze::FindNeighborsForSolveFunction(Queue& TUR, Point& temp)
{
	//The function puts to the QUEUE all the Neighbors of the point (POINT in the maze).
	//by the order: right, down, left, up.
	int row = temp.getX();
	int col = temp.getY();
	if (TheMaze[row][col + 1] == EMPTY) //right nebighbor
		TUR.EnQueue(Point(row, col + 1));
	if (TheMaze[row + 1][col] == EMPTY)//down nebighbor
		TUR.EnQueue(Point(row + 1, col));
	if (TheMaze[row][col - 1] == EMPTY) //left nebighbor
		TUR.EnQueue(Point(row, col - 1));
	if (TheMaze[row - 1][col] == EMPTY) //up nebighbor
		TUR.EnQueue(Point(row - 1, col));
}

//====================HELPERS FUNCTIONS====================//
//---------------------------------------------------------------------------------------------//
void Maze::setAcertainMazePoint(const char ch, const int row, const int col) { TheMaze[row][col] = ch; }

//============================================PUBLIC METHODS===============================================//
//GETTERS
//---------------------------------------------------------------------------------------------------//
int Maze::getRow() const { return this->Row; }
//---------------------------------------------------------------------------------------------------//
int Maze::getCol() const { return this->Col; }
//---------------------------------------------------------------------------------------------------//
char** Maze::getMaze() const { return TheMaze; }
//---------------------------------------------------------------------------------------------------//

//OTHERS
//---------------------------------------------------------------------------------------------------//
void Maze::MakeArandomeMaze()
{
	STACK stack;
	Point newNeighboor;
	this->InitiateRandomMaze();
	stack.Push(Point(1, 1));//Initiate stack

	while (!stack.IsEmpty()) //if stack != empty
	{
		Point temp = stack.Pop();
		this->setAcertainMazePoint(Maze::VISTED, temp.getX(), temp.getY()); //puting &
		this->checkForNeighboorsAndChooseOne(temp, newNeighboor);
		if (newNeighboor.getX() != 0 || newNeighboor.getY() != 0) //there is a newNeigboors
		{
			stack.Push(temp);
			stack.Push(newNeighboor);
		}
		this->removeNeihboors(); //clealing the Negiboors array
	}
	this->cleanTheMaze(); //cleaning all the $ (visited sign) from the Maze
}
//---------------------------------------------------------------------------------------------------//
void Maze::SolveTheMaze()
{
	int size = (Row) * (Col);
	int tempRow, tempCol;
	bool answer = false;
	Queue TUR(size);
	Point* temp;
	Point end((Row - 2), (Col - 1)); //the exit point from the maze
	TUR.EnQueue(Point(1, 0)); // initialization the QUEUE

	while (!(TUR.IsEmpty()) && !answer) //until the QUEUE Is empty
	{
		temp = new Point(TUR.DeQueue()); // geting the point (point on the maze) from the head of QUEUE
		tempRow = temp->getX();
		tempCol = temp->getY();
		TheMaze[tempRow][tempCol] = VISTED; //put $ in point on the maze that we already visited
		if ((tempRow == end.getX()) && (tempCol == end.getY())) //TRUE when we are in the exit point of the maze
			answer = true;
		FindNeighborsForSolveFunction(TUR, *temp);
		delete temp;
	}
	if (answer)
		printMAZE();
	else
		cout << "no solution\n";
}
//---------------------------------------------------------------------------------------------------//
void Maze::checkIfVaildMaze() const
{
	int firstRow = 0, lastRow = (Row - 1);
	int firstCol = 0, lastCol = (Col - 1);
	bool flag = true;
	for (int i = 0; i < Col && flag; i++) //checking the border UP && DOWN
	{
		if (TheMaze[firstRow][i] != WALL)
			flag = false;
		if (TheMaze[lastRow][i] != WALL)
			flag = false;
	}
	if (TheMaze[1][0] != EMPTY)
		flag = false;
	if (TheMaze[lastRow - 1][lastCol] != EMPTY)
		flag = false;
	for (int j = 2; j < Row && flag; j++)
	{
		if (TheMaze[j][firstCol] != WALL)
			flag = false;
	}


	for (int k = 0; k < lastRow - 2 && flag; k++)
	{
		if (TheMaze[k][lastCol] != WALL)
			flag = false;
	}
	if (!flag)
	{
		cout << "invalid input\n";
		exit(-1);
	}
}
//---------------------------------------------------------------------------------------------------//

void Maze::checkInputAndSetStrInMaze(int line, const char* str)
{
	int sizeString = strlen(str);
	bool flag = true;
	int idx = 0;

	//check if the input is more the the Col
	if (sizeString > Col)
		flag = false;

	for (idx; idx < Col && flag; idx++) //checking the input and put it inside the MAZE
	{
		if (str[idx] == WALL)
			TheMaze[line][idx] = WALL; // '*'
		else if (str[idx] == EMPTY)
			TheMaze[line][idx] = EMPTY;// ' '
		else
			flag = false; //Not Good INPUT
	}
	if (!flag)
	{
		cout << "invalid input\n";
		exit(1);
	}
}

//---------------------------------------------------------------------------------------------------//
void Maze::printMAZE() const
{
	int IdxRow, IdxCol;
	for (IdxRow = 0; IdxRow < Row; IdxRow++)
	{
		for (IdxCol = 0; IdxCol < Col; IdxCol++)
			cout << this->TheMaze[IdxRow][IdxCol];
		cout << endl;;
	}
}
//---------------------------------------------------------------------------------------------------//


