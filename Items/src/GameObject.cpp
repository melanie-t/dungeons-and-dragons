//! @file GameObject.cpp
//! @brief Implementation file for the GameObject class  
//!
#include "GameObject.h"
#include <iostream>
using namespace std;

//! Default Constructor for GameObject
//! sets the objectType to an empty string.
GameObject::GameObject()
{
	this->objectType = "";
}
//! GameObject constructor
//! @param objectType the type of GameObject this is.
GameObject::GameObject(std::string objectType)
{
	this->objectType = objectType;
}