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
	Map* destination;
	Map* prev;
	bool start;
public:
	//Door();
	Door(Map* destination, bool start = false);
	Door(bool start = false);

	Map* getDestination(){ return destination; }
	void setDestination(Map* dest){ destination = dest; }

	int getStart(){ return this->start; }
	void setStart(bool s){ this->start = s; }
};