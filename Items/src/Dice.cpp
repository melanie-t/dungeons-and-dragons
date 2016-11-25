
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

#include "Dice.h"
#include <iostream>
#include <iterator>
#include <regex>		// to parses strings
#include <stdlib.h>     // for random numbers
#include <time.h>       // helps initializes rand generator

using namespace std;

Dice::Dice() 
{
		number, type, total = 0;
		srand(time(NULL));							//initialize random #s
};


/* function will parse string and caclulate rolls */
int Dice::roll(string str) {
	number = 0;									// reinitialize values
	type = 0;
	total = 0;

	if (parseString(str)) 
	{						// parses string and sets values for number/dice/total
		total = sum(number, type, total);
		return total;
	}
	else {
		cout << "String parse error. Dice roll = 0" << endl;
		return 0;
	}
}

/* method works the same way but console out the steps involved */
int Dice::sayRoll(string str) {
	number = 0;
	type = 0;
	total = 0;

	if (parseString(str)) {
		cout << "number of dice: " << number << endl;
		cout << "type of die: " << type << endl;
		cout << "given total: " << total << endl << endl;
		return saySum(number, type, total);
	}
	else{
		cout << "String parse error. Dice roll = 0" << endl;
		return 0;
	}
}

/* Function to parse the string using regex commands and class */
bool Dice::parseString(string str) {
	string hand = str;									//user string to parse
	string parseResult[3];								//array holds parse values

	try {
		int iterateArr = 0;
		regex searchParam("\\d+");						//search parameters of string, grabs digits only
		sregex_iterator nextInt(hand.begin(), hand.end(), searchParam);		//defines individual elements found in string
		sregex_iterator end;
		while (nextInt != end) 
		{
			smatch match = *nextInt;
			parseResult[iterateArr] = match.str();		//note: the elements are saved as string type
			iterateArr++;
			nextInt++;
		}
	}
	catch (regex_error& e) 
	{
		cout << "error in regex: " << e.code() << endl;
	}

	try {
		//changed to atoi, since stoi was giving exceptions.
		number = atoi(parseResult[0].c_str());//stoi(parseResult[0]);		//stoi() std function that casts string to int
		type = atoi(parseResult[1].c_str());//stoi(parseResult[1]);
		total = atoi(parseResult[2].c_str());//stoi(parseResult[2]);
		//return true;
	}
	catch (exception e) {
		cout << endl << e.what() << endl;//"exception in parseResult assignment" << endl;
	}
	return true;
}


/* rolls dice based on amount of dice and type of die */
int Dice::sum(int n, int t, int tot) {
	number = n;
	type = t;
	total = tot;
	int temp;		
	int lowest = 6;
	cout << "[Your Rolls] ";
	while (number != 0)
	{
		temp = getRandom();
		if (temp < lowest)
			lowest = temp;
		total += temp;
		cout << temp << " ";
		number--;
	}
	total = total - lowest;
	cout << " Removed (" << lowest << ")  Total " << total << endl;
	return total;
	}

int Dice::saySum(int n, int t, int tot) {
	number = n;
	type = t;
	total = tot;
	int temp;

	while (number != 0) {
		temp = getRandom();
		total += temp;
		cout << "random number: " << temp << " running total: " << total << endl;
		number--;
	}

	return total;
}

/* generates random number based on size of die */
int Dice::getRandom() {
	switch (type) {
	case 4: {
		//cout << "selected 4 die" <<endl;
		return  (rand() % 4 + 1);
		break;
	}
	case 6: {
		//cout <<"selected 6 die" <<endl;
		return (rand() % 6 + 1);
		break;
	}
	case 8: {
		//cout << "selected 8 die" << endl;
		return  (rand() % 8 + 1);
		break;
	}
	case 10: {
		//cout << "selected 10 die" << endl;
		return  (rand() % 10 + 1);
		break;
	}
	case 12: {
		//cout << "selected 12 die" << endl;
		return  (rand() % 12 + 1);
		break;
	}
	case 20: {
		//cout << "selected 20 die" << endl;
		return  (rand() % 20 + 1);
		break;
	}
	case 100:
	{
		//cout << "selected 100 die" << endl;
		return  (rand() % 100 + 1);
		break;
	}
	default:
	{
		cout << endl << "getRandom() switch default, returning total of 0. Something went wrong yo." << endl;
		cout << "Please choose a supported die type. (d4,d8,d10,d12,d20,d100)" << endl;
		total = 0;
		return total;
		break;
	}
	}
}

// main method for testing
/*
int main() {
Dice dice;								//creating dice object
string a = "4d6[0]";
cout << "Final total: " << dice.roll(a) << endl;
cout << "Final total: " << dice.roll(a) << endl;
cout << "Final total: " << dice.roll(a) << endl;
cout << "Final total: " << dice.roll(a) << endl;
cin >> a;
return 0;
}
*/


