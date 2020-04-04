#ifndef _STACK_H
#define _STACK_H
#include "Point.h"
#include "Node.h"

class STACK
{
private: //Varibale
	Node* top;

public://C'tor, D'tor Methods
	STACK();
	~STACK();

public: //Mthods
	void MakeEmpty();
	int IsEmpty();
	void Push(Point item);
	Point Pop();
	Point Top();
};
#endif //_STACK_H
