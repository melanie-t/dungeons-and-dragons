#include "Character.h"

//This is BAD. find a way to change it later.
class Enemy : public Character, public GameObject 
{
public:
	Enemy();
};