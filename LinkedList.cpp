#include "LinkedList.h"

// default constructor
LinkedList::LinkedList()
{
	head = nullptr;
}

// function: enqueue
void LinkedList::enqueue(Node *ship)
{
	// declare and initialize variables
	static Node *last = head;	// hold on to the end of the list

	// if the list is NULL, then temp is the head
	if (head == nullptr)
	{
		head = ship;
		last = head;
	}

	// if there is at least 1 element in the list
	else
	{
		last->set_next_ship(ship);	// link the new ship to the end of the list
		last = last->get_next();	// move last 
	}

}

Node * LinkedList::dequeue()
{
	// declare and initialize variable
	Node *remove = head;	// hold the old head to remove from the queue
							// this will get assigned to another node pointer in main.cpp

	// if the list is empty, return nullptr
	if (head == nullptr)
		return nullptr;

	// if the list is not empty
	else
	{
		head = head->get_next();		// move head to the next node in the list
		remove->break_link();			// break the link between the old head and the rest of the list
	}
	
	return remove;
}

// function: is empty
bool LinkedList::is_empty()
{
	// if head is null - the queue is empty - return true. Otherwise, return false.
	if (head == nullptr)
		return true;
	else
		return false;
}
