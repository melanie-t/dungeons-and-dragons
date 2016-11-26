/* Documentation at tail of file */
#pragma once
#include <string>
#include "Observable.h"

using std::string;

class Dice : public Observable
{
public:

	/* Constructor*/
	Dice();

	/* function will parse string and caclulate rolls */
	int roll(string str);

	/* method works the same way but console out the steps involved */
	int sayRoll(string str);

	/* displays information of dice roll for logger*/
	void displayCurrentState();

private:
	int numTemp;		// non-incrementing number for bookkeeping purposes
	int number;			// number of dice to roll
	int type;			// type of dice: d4,d8,d10,d12,d20,d100
	int total = 0;		// total to output to user
	string lastRoll;

	/* Function to parse the string using regex commands and class */
	bool parseString(string str);
	
	/* rolls dice based on amount of dice and type of die */
	int sum(int n, int t, int tot);

	/* Prints out sum to user */
	int saySum(int n, int t, int tot);

	/* generates random number based on size of die */
	int getRandom();
};

/*
This class is a random number generator for dice rolls based on user specifications.
Dice which available to roll are of 4, 8, 10, 12, 20, and 100 'sides'. The algorithms
allow any number of any SINGLE one of these dice to be rolled and their totals are
summed appropriately. Support is included for a running total to be summed to the
new number/types of dice to be rolled.

The string parser looks for groups digits separated by any other character type.
At the moment the class only supports 3 sets of integers any more or less causes errors
in memory pointers.																				**to be fixed

The format to be given as a parameter to the ONLY public Dice method '.roll()':
Class supports number of die greater than 0 and of type 'int',									***cases of floats unsupported
Additionally, the function '.sayRoll()' will display the instance variables, random numbers,
and running total to the console. If negative numbers are given will respond as if positive.	***is this a problem?

'numberOfRolls' d 'typeOfDie' [ + 'valueToInclude' ]

ex.
5d4[+100]
rolls a 4 die 5 times, sums the total and adds 100

[Use]

Dice dice;							// creates a new dice object
string shake = "5d0[+100]";			// format of string to give to method
int rollOutcome;					// variable to hold roll value
rollOutcome = dice.roll(shake);		// rollOutcome will have the final sum
dice.clearRoll();					// reinitializes values to 0 **should functionality be added to roll???

[end Use]

If we want to add the roll outcome to another dice roll of another type, that functionality would
need to occur outside of the Dice class.
*/