#ifndef _POINT_H
#define _POINT_H

#include <iostream>
using namespace std;

class Point
{
private:
	int x;
	int y;

public:
	friend class Queue;
	Point(int x = 0, int y = 0); //defult
	Point(const Point& other);
	Point(const Point&& other);
	~Point();

public:
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	void show() const;
};

#endif // _point_H