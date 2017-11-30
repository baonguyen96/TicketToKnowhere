#ifndef TICKET_H
#define TICKET_H
#include "Meter.h"
#include <fstream>
using namespace std;

// forward declaration
class Ticket;
ofstream &operator << (ofstream &, const Ticket &);

class Ticket
{
private:
	Node *ship_info;
	Meter *meter_info;
	int hour_out;
	int minute_out;
	int overtime;
public:
	// constructors
	Ticket();
	Ticket(int, int, int, Meter &);

	// destructor
	~Ticket(){};

	// accessor
	Node * get_ship_info() const
	{	return ship_info;	}

	Meter * get_meter_info() const
	{	return meter_info;	}

	int get_hour_out() const
	{	return hour_out;	}

	int get_minute_out() const
	{	return minute_out;	}

	int get_overtime() const
	{	return overtime;	}

	// mutator
	void set_ticket(int, int, int, Meter&);		// set up a ticket for a particular ship
	void clear_ticket();						// reset ticket

	// overloaded output operator <<
	friend ofstream &operator << (ofstream &, Ticket &);

};

#endif