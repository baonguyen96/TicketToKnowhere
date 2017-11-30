#pragma warning (disable: 4996)

#include "Node.h"
#include <cstring>


// default constructor
Node::Node()
{
	// allocate new memories
	name = new char[50];
	id = new char[20];
	credit = 0;

	strncpy(name, "", 50);
	strncpy(id, "", 20);
	credit = 0;
	next = nullptr;
}


// overloaded constructor
Node::Node(char *n, char *i, int c)
{
	name = new char[50];
	id = new char[20];
	credit = 0;

	strncpy(name, n, 50);
	strncpy(id, i, 20);
	credit = c;
	next = nullptr;
}


// destructor
Node::~Node()
{
	delete[] name;
	delete[] id;
}

// function: set ship
void Node::set_ship(char *n, char *i, int c)
{
	strncpy(name, n, 50);
	strncpy(id, i, 20);
	credit = c;
	next = nullptr;
}
