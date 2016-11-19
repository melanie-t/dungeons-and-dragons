//! @file 
//! @brief Implementation file for the Door class  
//!
#include "Door.h"

//! Constructor for the Door class
//! @param start boolean to see if the door is the start or end
Door::Door(bool start) : Door(nullptr, start)
{
}
//! Constructor for the Door class
//! @param destinationID destination of the door
//! @param start boolean to see if the door is the start or end
Door::Door(Map* destination, bool start) : GameObject(OBJ_DOOR)
{
	this->destination = destination;
	this->start = start;
}