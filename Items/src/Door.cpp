#include "Door.h"

Door::Door()
{
	Door(0);
}
Door::Door(int destinationID)
{
	GameObject(DOOR);
	this->destinationID = destinationID;
}