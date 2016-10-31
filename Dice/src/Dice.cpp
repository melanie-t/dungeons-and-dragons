#include "Dice.h"
#include <iostream>
#include <iterator>
#include <string>
#include <regex>		// to parses strings
#include <stdlib.h>     // for random numbers
#include <time.h>       // helps initializes rand generator

using namespace std;

/* Default Constructor */
Dice::Dice() {
	number, type, total = 0;
	srand(time(NULL));							//initialize random #s
};

/* function will parse string and caclulate rolls */
int DICE::roll(string str) {
	number = 0;									// reinitialize values
	type = 0;
	total = 0;

	if (parseString(str)) {						// parses string and sets values for number/dice/total
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
	else if (!parseString(str)) {
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
		while (nextInt != end) {
			smatch match = *nextInt;
			parseResult[iterateArr] = match.str();		//note: the elements are saved as string type
			iterateArr++;
			nextInt++;
		}
	}
	catch (regex_error& e) {
		cout << "error in regex" << endl;
	}	try {		number = stoi(parseResult[0]);		//stoi() std function that casts string to int
		type = stoi(parseResult[1]);
		total = stoi(parseResult[2]);
		//return true;
	}
	catch (exception e) {
		cout << endl << "exception in parseResult assignment" << endl;
	}	return true;
}

/* rolls dice based on amount of dice and type of die */
int Dice::sum(int n, int t, int tot) {
	number = n;
	type = t;
	total = tot;
	int temp;


	while (number != 0) {
		temp = getRandom();
		total += temp;
		number--;
	}

	return total;
}

/* like sum but console out steps */
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
	case 4:
		//cout << "selected 4 die" <<endl;
		return  (rand() % 4 + 1);
		break;

	case 8:
		//cout << "selected 8 die" << endl;
		return  (rand() % 8 + 1);
		break;

	case 10:
		//cout << "selected 10 die" << endl;
		return  (rand() % 10 + 1);
		break;

	case 12:
		//cout << "selected 12 die" << endl;
		return  (rand() % 12 + 1);
		break;

	case 20:
		//cout << "selected 20 die" << endl;
		return  (rand() % 20 + 1);
		break;

	case 100:
		//cout << "selected 100 die" << endl;
		return  (rand() % 100 + 1);
		break;

	default:
		cout << endl << "getRandom() switch default, returning total of 0. Something went wrong yo." << endl;
		cout << "Please choose a supported die type. (d4,d8,d10,d12,d20,d100)" << endl;
		total = 0;
		return total;
		break;
	}
}

/* main method for testing
int main() {
Dice dice;								//creating dice object
string a = "-0d-4[+-10000]";
cout << endl << "final total: " << dice.roll(a) << endl;
return 0;
}
*/

