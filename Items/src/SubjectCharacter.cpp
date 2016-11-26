#include "SubjectCharacter.h"
#include "Character.h"
#include <iostream>
using namespace std;

SubjectCharacter::SubjectCharacter() {
};
SubjectCharacter::SubjectCharacter(Character* c) {
	//Upon instantiation, attaches itself to a Character
	subject = c;
	subject->attach(this);
};
SubjectCharacter::~SubjectCharacter() {
	//Upon destruction, detaches itself from its Character      
	subject->detach(this);
};

//toggles loggin of game data
void SubjectCharacter::logCharacter() {
	if (showLog) {
		showLog = false;
	}
	else {
		showLog = true;
	}
}

//reacts to Observable class notify
void SubjectCharacter::Update() {
	//calls the method in the class which displys the state of the object
	if (showLog) {
		subject->displayCurrentState();
	}
};
