#ifndef _MAZE_H
#define _MAZE_H

#include <string.h>
#include <iostream>
#include "Point.h"
#include "Queue.h"
#include "Stack.h"

#include <time.h>
#include <stdlib.h>

#pragma warning(disable : 4996)

using namespace std;

class Maze
{
public:
	static const char EMPTY = ' ';
	static const char WALL = '*';
	static const char VISTED = '$';
	static const int MAX_NIGHBOORS = 4;
	static const int left = 0;
	static const int up = 1;
	static const int right = 2;
	static const int down = 3;
	static const int No_Neigboors = -1;
	static const int MAX_COL_ROW = 80;

private:
	int Row;
	int Col;
	char** TheMaze;
	Point Neighboors[MAX_NIGHBOORS];


public: //C'tor, D'tor, Copy, Move
	Maze(const int row, const int col);
	Maze(const Maze& other);
	Maze(Maze&& other);
	~Maze();

private: // Private General Methods
	void AllocationEmptyMaze();
	bool setRow(const int& Row);
	bool setCol(const int& Col);

private:
	//HELPERS FOR FUNCTION RANDOM MAZE
	void InitiateRandomMaze();
	void checkForNeighboorsAndChooseOne(Point& currVerctor, Point& newNeighboor);
	void CreatingNeigboorsArray(int& x, int& y);
	int findNeighboorForRand();
	void removeNeihboors();
	void cleanTheMaze(); //Clean the $ on the maze

	//HELPERS FOR FUNCTION YOUR OWN MAZE
	void FindNeighborsForSolveFunction(Queue& TUR, Point& temp);

	//HELPERS
	void setAcertainMazePoint(const char ch, const int row, const int col);

public: //Public Methods
	//GETTERS
	char** getMaze() const;
	int getRow() const;
	int getCol() const;

	//MAIN
	void MakeArandomeMaze();
	void SolveTheMaze();
	void checkIfVaildMaze() const;
	void checkInputAndSetStrInMaze(int line, const char* str);
	void printMAZE() const;



};
#endif //_MAZE_H