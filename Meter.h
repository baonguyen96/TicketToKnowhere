#ifndef METER_H
#define METER_H
#include "Node.h"

class Meter
{
private:
	int hour_in;
	int minute_in;
	Node *dock;			// point to docked ship
public:
	// constructors
	Meter();
	Meter(int, int, Node *);

	// destructor
	~Meter(){};

	// accessors
	int get_hour_in() const
	{	return hour_in;	}

	int get_minute_in() const
	{	return minute_in;	}

	Node * get_ship() const
	{	return dock;	}

	// mutators
	void set_time_in(int, int);
	void set_docked_ship(Node *, int, int);		// put the ship into an open dock
	void clear_dock();							// remove ship from the dock

	void set_docked_ship_name(char *n)
	{	dock->set_ship_name(n);	}

	void set_docked_ship_ID(char *id)
	{	dock->set_ship_ID(id);	}

	void set_docked_ship_credit(int cred)
	{	dock->set_ship_credit(cred);	}

};

#endif