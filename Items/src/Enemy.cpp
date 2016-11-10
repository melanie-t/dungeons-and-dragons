//! @file 
//! @brief Implementation file for the Enemy class  
//!
#include "Enemy.h"

//! Default Constructor for Enemy class
//! sets all stats to 1.
Enemy::Enemy() : Enemy(1, 1, 1, 1, 1, 1, 1)
{

}

//!  Constructor for enemy class.
//! @param lvl level of enemy
//! @param str Strength of enemy
//! @param dex dexterity of enemy
//! @param con constitution of enemy
//! @param intel intellgigence of enemy
//! @param wis wisdom of enemy
//! @param cha charisma of enemy
Enemy::Enemy(int lvl, int str, int dex, int con, int intel, int wis, int cha) : 
		Character(lvl, str, dex, con, intel, wis, cha), GameObject(ENEMY)
{
}

//! randomize function
//! created a random enemy based of the player, 
//! all stats are within +/-5 the stats of the player
//! @param player player of map or campaign
Enemy* Enemy::randomize(Character* player)
{
	//For each stat, the enemy will within a range of +/- 5  of that.
	//The lvl will be the same.
	//May change in the future.
	int str = (rand() % 10 - 5) + player->getSTR();
	int dex = (rand() % 10 - 5) + player->getDEX();
	int con = (rand() % 10 - 5) + player->getCON();
	int intel = (rand() % 10 - 5) + player->getINTEL();
	int wis = (rand() % 10 - 5) + player->getWIS();
	int cha = (rand() % 10 - 5) + player->getCHA();

	return new Enemy(player->getLevel(), str, dex,con,intel,wis,cha);
}