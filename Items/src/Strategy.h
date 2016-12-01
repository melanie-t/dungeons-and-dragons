#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include "pos.h"

class Strategy
{
public:
	virtual int execute(pos characterPos, pos targetPos, std::vector<int> level, int width, int length, int lastkey = -1, sf::Event* evt = nullptr) = 0;
};