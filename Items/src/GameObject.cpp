#include "GameObject.h"

GameObject::GameObject()
{
	this->objectType = "";
}
GameObject::GameObject(std::string objectType)
{
	this->objectType = objectType;
}