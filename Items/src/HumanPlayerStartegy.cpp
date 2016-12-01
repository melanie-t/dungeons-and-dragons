#include "HumanPlayerStrategy.h"
#include "Door.h"
#include "Enemy.h"
#include "Friend.h"
#include "TileTypes.h"
#include "PlayerActionTypes.h"

//! execute function
//! determines move of human character
//! @param characterPos position of character
//! @parama targetPos posiiton of target character
//! @parama level array of levle
//! @prama width of map
//! @param lastKey last key entered
//! @param evt event
int HumanPlayerStrategy::execute(pos characterPos, pos targetPos, std::vector<int> level, int width, int length, int lastkey, sf::Event* evt)
{
	if (evt != nullptr)
	{
		if (evt->type == sf::Event::KeyReleased)
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
			case sf::Keyboard::Z:
			{
				return PlayerAction::LOOTING;
			}
			}
		}
	}
	return -1;
}