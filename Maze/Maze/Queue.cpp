#include "Queue.h"
//============================================COUNSTACTOR AND DESTRACTOR===============================================//

int Queue::AddOne(int x)
{
	return ((1 + x) % (Queue::size));
}

Queue::Queue(int size) :size(size)
{
	makeEmpty();
	data = new Point[size];
}

Queue::~Queue()
{
	delete[]data;
}


//============================================PUBLIC METHODS===============================================//
void Queue::makeEmpty()
{
	tail = 0;
	head = 1;
}
//---------------------------------------------------------------------------------------------------//
bool Queue::IsEmpty()
{
	if (AddOne(tail) == head)
		return true;
	else
		return false;
}
//---------------------------------------------------------------------------------------------------//
Point Queue::ShowFirst()
{
	if (IsEmpty())
	{
		cout << "EMPTY\n";
		exit(-1);
	}
	return data[head];
}
//---------------------------------------------------------------------------------------------------//
void Queue::EnQueue(Point item)
{
	if (AddOne(AddOne(tail)) == head)
		cout << "QUEUE FULL\n";

	tail = AddOne(tail);
	data[tail].x = item.x;
	data[tail].y = item.y;
}
//---------------------------------------------------------------------------------------------------//
Point Queue::DeQueue()
{
	if (IsEmpty())
	{
		cout << "ERROR\n";
	}
	Point item = data[head];
	head = AddOne(head);
	return item;
}
//---------------------------------------------------------------------------------------------------//
