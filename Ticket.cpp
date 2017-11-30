#include "Ticket.h"
#include <fstream>
#include <iomanip>

// default constructor
Ticket::Ticket()
{
	ship_info = nullptr;
	meter_info = nullptr;
	hour_out = 0;
	minute_out = 0;
	overtime = 0;
}

// overloaded constructor
Ticket::Ticket(int h, int m, int over, Meter &dock)
{
	ship_info = dock.get_ship();
	meter_info = &dock;				// memberwide assignment
	hour_out = h;
	minute_out = m;
	overtime = over;
}

// function: set ticket
void Ticket::set_ticket(int h, int m, int over, Meter &dock)
{
	ship_info = dock.get_ship();
	meter_info = &dock;				// memberwide assignment
	hour_out = h;
	minute_out = m;
	overtime = over;
}

// function: clear ticket
void Ticket::clear_ticket()
{
	// reset everything to null or 0
	ship_info = nullptr;
	meter_info = nullptr;
	hour_out = 0;
	minute_out = 0;
	overtime = 0;
}

// overloaded output operator
ofstream &operator << (ofstream &output_file, Ticket &ticket)
{
	// write to the ouput file in the following format
	output_file << "Ship ID: " << ticket.get_ship_info()->get_id() << endl
		<< "Name: " << ticket.get_ship_info()->get_name() << endl
		<< "Time In: " << setw(2) << setfill('0') << ticket.get_meter_info()->get_hour_in() << ':'
		<< setw(2) << setfill('0') << ticket.get_meter_info()->get_minute_in() << endl
		<< "Time Out: " << setw(2) << setfill('0') << ticket.get_hour_out() << ':'
		<< setw(2) << setfill('0') << ticket.get_minute_out() << endl
		<< "Credited Minutes: " << ticket.get_ship_info()->get_credit() << endl
		<< "Extra Minutes: " << ticket.get_overtime() << endl
		<< "Fine: " << ticket.get_overtime() * 2000 << " units" << endl << endl;

	return output_file;
}