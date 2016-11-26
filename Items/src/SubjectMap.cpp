#include "SubjectMap.h"
#include "Map.h"
#include <iostream>
using namespace std;

SubjectMap::SubjectMap() {
};
SubjectMap::SubjectMap(Map* s) {
	//Upon instantiation, attaches itself to a Map
	subject = s;
	subject->attach(this);
};
SubjectMap::~SubjectMap() {
	//Upon destruction, detaches itself from its Map      
	subject->detach(this);
};

// toggles showing the map log information
void SubjectMap::logMap() {
	if (showLog) {
		showLog = false;
	}else{
		showLog = true;
	}
}

//reacts to Observable class notify
void SubjectMap::Update() {
	//calls the method in the class which displys the state of the object
	if (showLog) {
		subject->displayCurrentState();
	}
};
