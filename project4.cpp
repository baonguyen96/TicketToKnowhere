//
// Project 4
//
// By:	Bao Nguyen
//		bcn140030
//		CS 1337.007
//

#include <iostream>
#include "Node.h"
#include "Meter.h"
#include "LinkedList.h"
#include "Ticket.h"
#include <iomanip>
#include <cstring>
#include <cctype>
#include <fstream>
using namespace std;

// global variable
const int DOCK_STATION = 10;		// 10 docking stations
const int BUFFER = 40;				// size of input char array

// function prototypes
int check_available_dock(Meter[]);				// check any available dock
int check_overtime(Meter[], int, int, int);		// check if the ship stays overtime
int search_ship(Meter[], char *);				// find the ship from the Meter array to pull out
void set_time_in(int &, int &);					// set the time the ship dock after retrieving from the queue

// function: main
int main()
{
	// declare & initialize variables
	Ticket violation_ticket;							// generate ticket if the ship stays overtime
	Meter docking_station[DOCK_STATION];				// 10 docking stations
	LinkedList queue;									// head of the list
	ifstream input_file("Knowhere.dat");				// file containing ships info
	ofstream output_file("Tickets.txt", ios::app);		// file containing tickets data
	char c,												// hold each character from the input file
		input[BUFFER] = "",								// collect characters c to form a word
		name[BUFFER] = "",								// name of the ship
		id[BUFFER] = "",								// ship's ID
		temp[2] = "";									// tmeporary cstring to add to the input cstring
	bool enter = false,									// mark the entering ship
		exit = false,									// mark the leaving ship
		found_name = false,
		found_id = false,
		found_hour_in = false,
		found_hour_out = false,
		found_minute_in = false;
	int location = -1,									// the array element
		hour_out = 0,
		minute_out = 0,
		hour_in = 0,
		minute_in = 0,
		credit = 0,
		overtime = 0;
	unsigned int index = 0;								// use in for loops to reset cstring

	// if cannot open the file, display an error message to the screen
	if (input_file.fail())
	{
		cout << "Error. Cannot open the file \"Knowhere.dat\"" << endl << endl;
		return 0;
	}
	else
		cout << "Processing the file \"Knowhere.dat\"..." << endl << endl;

	// read till the end of the input file
	do
	{
		// get character from the file
		input_file.get(c);
		
		// skip the whitespace, colon, new line, or end of file characters
		if (!isspace(c) && c != '\n' && c != ':' && !input_file.eof())
		{
			temp[0] = c;
			strncat(input, temp, BUFFER);
		}
		
		// if c is a white space, a colon, or a new line
		else
		{
			// if the ship is entering the station
			if (strncmp(input, "enter", BUFFER) == 0)
			{
				enter = true;

				// check available dock
				location = check_available_dock(docking_station);

				goto RESET_INPUT;
			}

			// if the ship is leaving the station
			if (strncmp(input, "exit", BUFFER) == 0)
			{
				exit = true;
				goto RESET_INPUT;
			}

			// if the character is a colon
			if (c == ':')
			{
				// if the ship is entering the port
				if (enter)
				{
					found_hour_in = true;
					hour_in = atoi(input);
					goto RESET_INPUT;
				}

				// if the ship is leaving the port
				if (exit)
				{
					found_hour_out = true;
					hour_out = atoi(input);
					goto RESET_INPUT;

				}
				
			}	// end if (c is ":")

			// if c is a whitespace character
			if (isspace(c))
			{
				// if the ship is entering the port
				if (enter)
				{
					// set minute in
					if (!found_minute_in)
					{
						minute_in = atoi(input);
						found_minute_in = true;

						goto RESET_INPUT;
					}

					// if the name has not been found, set it to true and assign the name to the ship
					if (found_minute_in && !found_name)
					{
						found_name = true;
						strncpy(name, input, BUFFER);
						
						goto RESET_INPUT;
					}

					// set ship ID
					if (found_minute_in && found_name && !found_id)
					{
						found_id = true;
						strncpy(id, input, BUFFER);
						
						goto RESET_INPUT;
					}

					// set ship credit
					if (found_minute_in && found_name && found_id)
						credit = (atoi(input));
						

				}	// end if(enter)

				// if the ship is leaving the port
				if (exit)
				{
					// set ship iD
					if (!found_id)
					{
						strncpy(id, input, BUFFER);
						found_id = true;
						goto RESET_INPUT;
					}

				}	// end if (exit)

			}	// end if (c is white space)

			// if the character is a new line, reset/process every thing and loop again
			if (c == '\n' || input_file.eof())
			{
				// if the ship is entering the port
				if (enter)
				{
					// create new ship & set its information
					Node *ship = new Node;
					ship->set_ship(name, id, credit);
					
					// if there is any empty docking station, put the ship there
					if (location != -1)
						docking_station[location].set_docked_ship(ship, hour_in, minute_in);

					// if the dock is full, put the ship to queue
					else
						queue.enqueue(ship);

				}	// end if (enter)

				// if the ship is leaving the station
				if (exit)
				{
					// set minute out
					minute_out = atoi(input);

					// find the docking station of the specific ship
					location = search_ship(docking_station, id);

					// check if the ship stays overtime
					overtime = check_overtime(docking_station, location, hour_out, minute_out);

					// if the ship stays overtime, generate a ticket
					if (overtime > 0)
					{
						// create a ticket
						violation_ticket.set_ticket(hour_out, minute_out, overtime, docking_station[location]);

						// write the ticket to the file
						output_file << violation_ticket;

						// reset the ticket for the next use
						violation_ticket.clear_ticket();

					}	// end if (overtime)
					
					// delete the dynamic node (the ship that just leaves the array)
					delete docking_station[location].get_ship();

					// if there is any ship in the queue, add it to the dock
					if (!(queue.is_empty()))
					{
						// set time in
						hour_in = hour_out;
						minute_in = minute_out;

						// call function set time in to set up the new time in (15 mins later)
						set_time_in(hour_in, minute_in);

						// empty the spot
						docking_station[location].clear_dock();

						// create new node, remove the first ship in the queue
						Node *ship = new Node;
						ship = queue.dequeue();

						// put the ship into the array with the new time in (15 minutes after the other ship left)
						docking_station[location].set_docked_ship(ship, hour_in, minute_in);

					}	// end if(queue)

					// if the queue is empty, just clear out the current dock
					else
						docking_station[location].clear_dock();
					
				}	//end if (exit)

				// reset everything
				enter = false;								
				exit = false;
				found_name = false;
				found_id = false;
				found_hour_in = false;
				found_hour_out = false;
				found_minute_in = false;
				location = -1;
				hour_out = 0;
				minute_out = 0;
				hour_in = 0;
				minute_in = 0;
				overtime = 0;

				for (index = 0; index < BUFFER; index++)
				{
					name[index] = 0;
					id[index] = 0;
				}
				
			}	// end if (c is new line or eof)

			// reset input
			RESET_INPUT:
			for (index = 0; index < BUFFER; index++)
				input[index] = 0;
			
		}	// end else (c is a white space, a new line, or null)

	} while (!input_file.eof());	// repeat until reaching the end of input file

	// display message indicating that the program is done
	cout << "Finished reading \"Knowhere.dat\"" << endl
		<< "Tickets data has been written to the file \"Tickets.txt\"" << endl << endl;

	// close the files
	input_file.close();
	output_file.close();

	return 0;
}

// function: check available
int check_available_dock(Meter dock[])
{
	// loop through the entire array
	for (int index = 0; index < DOCK_STATION; index++)
	{
		// if find any empty element, then the dock is available
		if (dock[index].get_ship() == nullptr)
			return index;	// return the location of the dock
	}

	// if the return statement has not been triggered yet, the array is full. Return -1
	return -1;
}

// function: check overtime
int check_overtime(Meter dock[], int index, int hour_out, int minute_out)
{
	// declare & initialize variable
	int stay_time = 0,		// the actual time the ship stays at the dock
		over = 0;			// the over time the ship stays (in minutes)
	
	// if the hour in equals the hour out, and minute in is less than or equal to the minute out,
	// then the ship stay within a specific 1h block
	if (dock[index].get_hour_in() == hour_out && dock[index].get_minute_in() <= minute_out)
		stay_time = minute_out - dock[index].get_minute_in();

	// if hour in is less than hour out, then the ship stays to another 1h block
	else if (dock[index].get_hour_in() < hour_out)
	{
		// if minute in is less than or equal to the minute out, calculate stay time by the following formula
		if (dock[index].get_minute_in() <= minute_out)
			stay_time = (hour_out - dock[index].get_hour_in()) * 60 + (minute_out - dock[index].get_minute_in());

		// if minute in is more than minute out, calculate stay time by the following formula
		else
			stay_time = (hour_out - dock[index].get_hour_in() - 1) * 60 + (60 - dock[index].get_minute_in() + minute_out);
	
	}	// end else

	// calculate overtime
	// deference the specific dock to call its get_ship function, which return the pointer to the ship
	// then dereference the function (the pointer) to access its get_credit function, which return the reserved minutes
	over = stay_time - dock[index].get_ship()->get_credit();

	// if overtime is more than 0, return that time. Otherwise, return 0
	if (over > 0)
		return over;
	else
		return 0;
}

// function: search ship
int search_ship(Meter dock[], char *id)
{
	// loop through the entire array
	for (int index = 0; index < DOCK_STATION; index++)
	{
		// check to see if the spot is empty or not
		// if empty, move on. If not, compare the ship ID's
		if (dock[index].get_ship() != nullptr)
		{
			// if the name of the ship is found, return the index
			if (strncmp(dock[index].get_ship()->get_id(), id, BUFFER) == 0)
				return index;
		}
		
	}	// end for

	return -1;
}

// function: set time in
void set_time_in(int &hour_in, int &minute_in)
{
	// if minute in is less than 45, then the new minute in is itself + 15
	if (minute_in < 45)
		minute_in += 15;

	// if minute in is equal to or greater than 45,
	else
	{
		hour_in++;	// increment the hour in by 1
		minute_in = 15 - (60 - minute_in);	// new minute in is the difference between 15 and (60 - old minute in)
	}
}