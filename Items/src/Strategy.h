#pragma once

#include <SFML\Graphics.hpp>
#include "pos.h"

class Strategy
{
public:
	virtual int execute(pos characterPos, pos targetPos, int lastkey = -1, sf::Event* evt = nullptr) = 0;
};