#include "Meter.h"

// default constructor
Meter::Meter()
{
	minute_in = 0;
	hour_in = 0;
	dock = nullptr;
}

// overloaded connstructor
Meter::Meter(int h, int m, Node *ship)
{
	minute_in = m;
	hour_in = h;
	dock = ship;
}

// function: set time in
void Meter::set_time_in(int h, int m)
{
	hour_in = h;
	minute_in = m;
}

// function: set docked ship
void Meter::set_docked_ship(Node *ship, int h_in, int m_in)
{
	hour_in = h_in;
	minute_in = m_in;
	dock = ship;		// memberwise assignment
}

// function: clear dock
void Meter::clear_dock()
{
	// reset everything to 0 (int) or NULL (cstring)
	hour_in = 0;
	minute_in = 0;
	dock = nullptr;
}