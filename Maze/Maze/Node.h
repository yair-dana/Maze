#ifndef _NODE_H
#define _NODE_H

#include "Point.h"

class Node
{
private:
	Point data;
	Node* next;

public: //C'tor, D'tor, Copy, Move
	Node(Point data, Node* next);
	Node(Node& other) = delete;
	Node(Node&& other) = delete;
	~Node();
public: 	//Getter and Setters
	void setData(Point item);
	void setNext(Node* next);
	Point getData();
	Node* getNext();
};
#endif // _NODE_H
