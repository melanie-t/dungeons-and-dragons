#include "HumanPlayerStrategy.h"
#include "Door.h"
#include "Enemy.h"
#include "Friend.h"
#include "TileTypes.h"
#include "PlayerActionTypes.h"

int HumanPlayerStrategy::execute(pos characterPos, pos targetPos,int lastkey, sf::Event* evt)
{
	if (evt != nullptr)
	{
		switch (evt->key.code)
		{
		case sf::Keyboard::Up:
		{
			return PlayerAction::MOVE_UP;
		}
		case sf::Keyboard::Down:
		{
			return PlayerAction::MOVE_DOWN;
		}
		case sf::Keyboard::Left:
		{
			return PlayerAction::MOVE_LEFT;
		}
		case sf::Keyboard::Right:
		{
			return PlayerAction::MOVE_RIGHT;
		}
		case sf::Keyboard::A:
		{
			return PlayerAction::ATTACK;
		}
		}
	}
	return 0;
}