#include "SubjectDice.h"
#include "Dice.h"
#include <iostream>
using namespace std;

SubjectDice::SubjectDice() {
};
SubjectDice::SubjectDice(Dice* d) {
	//Upon instantiation, attaches itself to a Dice
	subject = d;
	subject->attach(this);
};
SubjectDice::~SubjectDice() {
	//Upon destruction, detaches itself from its Dice      
	subject->detach(this);
};

//adds new object to observer list
void SubjectDice::Add(Dice* d) {
	subject->attach(this);
}

//toggles loggin of game data
void SubjectDice::logDice() {
	if (showLog) {
		showLog = false;
	}
	else {
		showLog = true;
	}
}

//reacts to Observable class notify
void SubjectDice::Update() {
	//calls the method in the class which displys the state of the object
	if (showLog) {
		subject->displayCurrentState();
	}
};
