#pragma warning(disable: 4996)

#ifndef NODE_H
#define NODE_H
#include <cstring>
#include <iostream>
using namespace std;

// forward declaration
class Node;
istream &operator >> (istream &, Node &);

class Node
{
private:
	char *name;		// ship name
	char *id;		// ship ID
	int credit;		// total reserved minutes
	Node *next;		// point to the next ship in the queue
public:
	// constructors
	Node();
	Node(char *, char *, int);

	// destructor
	~Node();

	// accessors
	char *get_name() const
	{	return name;	}
	
	char *get_id() const
	{	return id;	}
	
	int get_credit() const
	{	return credit;	}
	
	Node * get_next() const
	{	return next;	}

	//mutators
	void set_ship(char *, char *, int);	

	void set_ship_name(char *n)			// set the name of the ship
	{	strncpy(name, n, 50);	}

	void set_ship_ID(char *i)			// set the ship ID
	{	strncpy(id, i, 20);	}

	void set_ship_credit(int c)			// set the ship credited minutes
	{	credit = c;	}

	void set_next_ship(Node *&next_ship)	// link with the next node
	{	next = next_ship;	}

	void break_link()						// break the link of the current node and the rest of the list
	{	next = nullptr;	}

	// overload input operator
	friend istream &operator >> (istream &stream, Node &object)
	{
		stream >> object.name >> object.id >> object.credit;

		return stream;
	}
	
};

#endif