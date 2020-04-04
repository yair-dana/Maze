#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>
#include "Point.h"

using namespace std;

class Queue
{
private:
	int head, tail;
	int size;
	Point* data;
	int AddOne(int x);

public:
	Queue(int size);
	Queue(const Queue& other) = delete;
	Queue(Queue&& other) = delete;
	~Queue();

	void makeEmpty();
	bool IsEmpty();
	Point ShowFirst();
	void EnQueue(Point item);
	Point DeQueue();
};

#endif // _QUEUE_H