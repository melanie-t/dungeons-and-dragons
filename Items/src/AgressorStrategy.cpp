#include "AgressorStrategy.h"
#include "MathHelper.h"
#include "PlayerActionTypes.h"
#include <thread>


int AgressorStrategy::execute(pos characterPos, pos targetPos, std::vector<int> level, int width, int lastkey, sf::Event* evt)
{
	//Make program wait 500ms before executing.
	//To simulate program "thinking"
	//std::this_thread::sleep_for(std::chrono::milliseconds(50)); 

	if (MathHelper::getDistance(characterPos, targetPos) <= 1)
	{
		return PlayerAction::ATTACK;
	}
	else
	{
		if (characterPos.x > targetPos.x)
		{
			return PlayerAction::MOVE_LEFT;
		}
		else if (characterPos.x < targetPos.x)
		{
			return PlayerAction::MOVE_RIGHT;
		}
		else if (characterPos.y > targetPos.y)
		{
			return PlayerAction::MOVE_UP;
		}
		else if (characterPos.y < targetPos.y)
		{
			return PlayerAction::MOVE_DOWN;
		}
	}
	return 0;
}