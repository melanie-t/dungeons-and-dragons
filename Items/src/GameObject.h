#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
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
#endif