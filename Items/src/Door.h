//! @file 
//! @brief Header file for the Door class  
//!
#include "GameObject.h"

class Door : public GameObject
{
private:
	int destinationID;
	bool start;
public:
	Door();
	Door(int destinationID, bool start = false);

	int getDestinationID(){ return this->destinationID; }
	void setDestinationID(int d){ this->destinationID = d; }

	int getStart(){ return this->start; }
	void setStart(bool s){ this->start = s; }
};