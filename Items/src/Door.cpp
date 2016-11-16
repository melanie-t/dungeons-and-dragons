//! @file 
//! @brief Implementation file for the Door class  
//!
#include "Door.h"

//! Default constructor for Door class
//! sets mapid to 0.
Door::Door() : Door(0)
{
}
//! Constructor for the Door class
//! @param start boolean to see if the door is the start or end
Door::Door(bool start) : Door(-1, start)
{
}
//! Constructor for the Door class
//! @param destinationID destination of the door
//! @param start boolean to see if the door is the start or end
Door::Door(int destinationID, bool start) : GameObject(DOOR)
{
	this->destinationID = destinationID;
	this->start = start;
}