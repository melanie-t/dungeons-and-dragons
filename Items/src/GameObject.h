//! @file GameObject.h
//! @brief Header file for the GameObject class  
//! Contains all of the game objects (Door, Enemy, Fighter, Item)
#pragma once

#include <string>
#include "ObjectTypes.h"

class GameObject
{
protected:
	std::string objectType;
public:
	GameObject();
	GameObject(std::string objectType);

	std::string getObjectType(){ return this->objectType; };
	void setObjectType(std::string type){ objectType = type; };
};