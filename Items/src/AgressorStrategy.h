#pragma once

#include "Strategy.h"

class AgressorStrategy : public Strategy
{
public:
	int execute(pos characterPos, pos targetPos, int lastkey = -1, sf::Event* evt = nullptr);
};