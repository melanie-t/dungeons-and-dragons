#include "SubjectGame.h"
#include "Game.h"
#include <iostream>
using namespace std;

SubjectGame::SubjectGame() {
};
SubjectGame::SubjectGame(Game* s) {
	//Upon instantiation, attaches itself to a Game
	subject = s;
	subject->attach(this);
};
SubjectGame::~SubjectGame() {
	//Upon destruction, detaches itself from its Game      
	subject->detach(this);
};

//toggles loggin of game data
void SubjectGame::logGame() {
	if (showLog) {
		showLog = false;
	}
	else {
		showLog = true;
	}
}

//reacts to Observable class notify
void SubjectGame::Update() {
	//calls the method in the class which displys the state of the object
	if (showLog) {
		subject->displayCurrentState();
	}
};
