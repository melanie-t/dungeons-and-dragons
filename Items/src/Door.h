#include "GameObject.h"

class Door : public GameObject
{
private:
	int destinationID;
public:
	Door();
	Door(int destinationID);

	int getDestinationID(){ return this->destinationID; }
	void setDestinationID(int d){ this->destinationID = d; }
};