#pragma once

#include "Strategy.h"

class FriendlyStrategy : public Strategy
{
public:
	int execute(pos characterPos, pos targetPos, std::vector<int> level, int width, int lastkey = -1, sf::Event* evt = nullptr);
};