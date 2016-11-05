#include "Enemy.h"

Enemy::Enemy() : Enemy(1, 9, 9, 9, 9, 9, 9)
{

}

Enemy::Enemy(int lvl, int str, int dex, int con, int intel, int wis, int cha) : 
		Character(lvl, str, dex, con, intel, wis, cha), GameObject(ENEMY)
{
}

Enemy Enemy::randomize(Character* player)
{
	//For each stat, the enemy will within a range of +/- 5  of that.
	//The lvl will be the same.
	int str = (rand() % 10 - 15) + player->getSTR();
	int dex = (rand() % 10 - 15) + player->getDEX();
	int con = (rand() % 10 - 15) + player->getCON();
	int intel = (rand() % 10 - 15) + player->getINTEL();
	int wis = (rand() % 10 - 15) + player->getWIS();
	int cha = (rand() % 10 - 15) + player->getCHA();

	return Enemy(player->getLevel(), str, dex,con,intel,wis,cha);
}