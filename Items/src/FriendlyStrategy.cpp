#include <thread>
#include <iostream>
#include "FriendlyStrategy.h"
#include "MathHelper.h"
#include "PlayerActionTypes.h"
#include "TileTypes.h"

//! execute function
//! determines move of friendly character
//! @param characterPos position of character
//! @parama targetPos posiiton of target character
int FriendlyStrategy::execute(pos characterPos, pos targetPos, std::vector<int> level, int width, int lastkey, sf::Event* evt)
{
	//std::this_thread::sleep_for(std::chrono::seconds(1));
	if (MathHelper::getDistance(characterPos, targetPos) <= 1)
	{
		return PlayerAction::ATTACK;
	}
	else
	{
		int currentPos = characterPos.y*width + characterPos.x;

		//Left
		if (characterPos.x > targetPos.x && level[currentPos - 1] != TileTypes::WATER
			&& level[currentPos - 1] != TileTypes::CHEST && level[currentPos - 1] != TileTypes::TREE
			&& level[currentPos - 1] != TileTypes::END)
		{
			return PlayerAction::MOVE_LEFT;
		}
		else if (characterPos.x > targetPos.x && level[currentPos - width] != TileTypes::WATER
			&& level[currentPos - width] != TileTypes::CHEST && level[currentPos - width] != TileTypes::TREE
			&& level[currentPos - width] != TileTypes::END)
		{
			return PlayerAction::MOVE_UP;
		}
		else if (characterPos.x > targetPos.x && level[currentPos + width] != TileTypes::WATER
			&& level[currentPos + width] != TileTypes::CHEST && level[currentPos + width] != TileTypes::TREE
			&& level[currentPos + width] != TileTypes::END)
		{
			return PlayerAction::MOVE_DOWN;
		}
		else if (characterPos.x > targetPos.x && level[currentPos + 1] != TileTypes::WATER
			&& level[currentPos + 1] != TileTypes::CHEST && level[currentPos + 1] != TileTypes::TREE
			&& level[currentPos + 1] != TileTypes::END)
		{
			return PlayerAction::MOVE_RIGHT;
		}

		//Move right
		if (characterPos.x < targetPos.x && level[currentPos + 1] != TileTypes::WATER
			&& level[currentPos + 1] != TileTypes::CHEST && level[currentPos + 1] != TileTypes::TREE
			&& level[currentPos + 1] != TileTypes::END)
		{
			return PlayerAction::MOVE_RIGHT;
		}
		else if (characterPos.x < targetPos.x && level[currentPos - width] != TileTypes::WATER
			&& level[currentPos - width] != TileTypes::CHEST && level[currentPos - width] != TileTypes::TREE
			&& level[currentPos - width] != TileTypes::END)
		{
			return PlayerAction::MOVE_UP;
		}
		else if (characterPos.x < targetPos.x && level[currentPos + width] != TileTypes::WATER
			&& level[currentPos + width] != TileTypes::CHEST && level[currentPos + width] != TileTypes::TREE
			&& level[currentPos + width] != TileTypes::END)
		{
			return PlayerAction::MOVE_DOWN;
		}
		else if (characterPos.x < targetPos.x && level[currentPos - 1] != TileTypes::WATER
			&& level[currentPos - 1] != TileTypes::CHEST && level[currentPos - 1] != TileTypes::TREE
			&& level[currentPos - 1] != TileTypes::END)
		{
			return PlayerAction::MOVE_LEFT;
		}

		//Move up
		if (characterPos.y > targetPos.y && level[currentPos - width] != TileTypes::WATER
			&& level[currentPos - width] != TileTypes::CHEST && level[currentPos - width] != TileTypes::TREE
			&& level[currentPos - width] != TileTypes::END)
		{
			return PlayerAction::MOVE_UP;
		}
		else if (characterPos.y > targetPos.y && level[currentPos - 1] != TileTypes::WATER
			&& level[currentPos - 1] != TileTypes::CHEST && level[currentPos - 1] != TileTypes::TREE
			&& level[currentPos - 1] != TileTypes::END)
		{
			return PlayerAction::MOVE_LEFT;
		}
		else if (characterPos.y > targetPos.y && level[currentPos + 1] != TileTypes::WATER
			&& level[currentPos + 1] != TileTypes::CHEST && level[currentPos + 1] != TileTypes::TREE
			&& level[currentPos + 1] != TileTypes::END)
		{
			return PlayerAction::MOVE_RIGHT;
		}
		else if (characterPos.y > targetPos.y && level[currentPos + width] != TileTypes::WATER
			&& level[currentPos + width] != TileTypes::CHEST && level[currentPos + width] != TileTypes::TREE
			&& level[currentPos + width] != TileTypes::END)
		{
			return PlayerAction::MOVE_DOWN;
		}
		//Move down.
		if (characterPos.y < targetPos.y && level[currentPos + width] != TileTypes::WATER
			&& level[currentPos + width] != TileTypes::CHEST && level[currentPos + width] != TileTypes::TREE
			&& level[currentPos + width] != TileTypes::END)
		{
			return PlayerAction::MOVE_DOWN;
		}
		else if (characterPos.y < targetPos.y && level[currentPos - 1] != TileTypes::WATER
			&& level[currentPos - 1] != TileTypes::CHEST && level[currentPos - 1] != TileTypes::TREE
			&& level[currentPos - 1] != TileTypes::END)
		{
			return PlayerAction::MOVE_LEFT;
		}
		else if (characterPos.y < targetPos.y && level[currentPos + 1] != TileTypes::WATER
			&& level[currentPos + 1] != TileTypes::CHEST && level[currentPos + 1] != TileTypes::TREE
			&& level[currentPos + 1] != TileTypes::END)
		{
			return PlayerAction::MOVE_RIGHT;
		}
		else if (characterPos.y < targetPos.y && level[currentPos - width] != TileTypes::WATER
			&& level[currentPos - width] != TileTypes::CHEST && level[currentPos - width] != TileTypes::TREE
			&& level[currentPos - width] != TileTypes::END)
		{
			return PlayerAction::MOVE_DOWN;
		}
	}
	return -1;
}