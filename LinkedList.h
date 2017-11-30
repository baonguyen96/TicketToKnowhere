#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "Node.h"

// all assignment is memberwide assignment in this class

class LinkedList
{
private:
	Node *head;		// first element in the queue
public:
	// constructor
	LinkedList();

	// destructor
	// only get destroyed when main.cpp terminates
	~LinkedList()
	{	delete head;	}

	// accessor
	Node * get_head() const
	{	return head;	}
	
	// mutator
	Node * set_head();

	// functions
	void enqueue(Node *);	// put the ship into the queue
	Node * dequeue();		// remove the ship from the queue
	bool is_empty();		// check to see if the queue is empty
};

#endif