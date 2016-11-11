//! @file 
//! @brief Header file for the GameObject class  
//!
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

	std::string getObjectType(){ return this->objectType; }
};