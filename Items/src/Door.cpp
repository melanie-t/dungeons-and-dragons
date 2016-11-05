#include "Door.h"

Door::Door() : Door(0)
{
}
Door::Door(int destinationID, bool start) : GameObject(DOOR)
{
	this->destinationID = destinationID;
	this->start = start;
}