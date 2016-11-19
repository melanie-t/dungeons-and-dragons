//! @file Door.h
//! @brief Header file for the Door class  
//! Implements Door object, child of GameObject
//! Methods to check if the Door we are on is the START or END of a map
#pragma once

#include "GameObject.h"
#include "Map.h"

class Door : public GameObject
{
private:
	int destinationID;
	Map* destination;
	bool start;
public:
	//Door();
	Door(int destinationID, bool start = false);
	Door(bool start = false);

	int getDestinationID(){ return this->destinationID; }
	void setDestinationID(int d){ this->destinationID = d; }

	Map* getDestination(){ this->destination; }

	int getStart(){ return this->start; }
	void setStart(bool s){ this->start = s; }
};