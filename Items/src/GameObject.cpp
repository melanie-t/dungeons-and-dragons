#include "GameObject.h"
#include <iostream>
using namespace std;

GameObject::GameObject()
{
	this->objectType = "";
}
GameObject::GameObject(std::string objectType)
{
	this->objectType = objectType;
}