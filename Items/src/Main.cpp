#include <thread>
#include <Windows.h>

//CharacterBuilder (Bully Fighter, Nimble Fighter, Tank Fighter)
//#include "CharacterCreater.h"
//#include "Bully.h"
//#include "Tank.h"
//#include "Nimble.h"
#include "Game.h"
#include "FileMapBuilder.h"
#include "SavedMapBuilder.h"
#include "Character.h"
#include "Fighter.h"
#include "Enemy.h"
#include "Door.h"
#include "Item.h"
#include "Markup.h"
#include "Friend.h"
#include "StatisticsHelper.h"
#include "Campaign.h"

//Observer and subject classes
#include "SubjectCharacter.h"
#include "SubjectDice.h"
#include "SubjectGame.h"
#include "SubjectMap.h"
#include "Dice.h"
#include <iostream>

using namespace std;

void main() {
	//Inifialize map, character, dice, game objects
	Dice *dice = new Dice;
	SubjectDice *subDice = new SubjectDice(dice);
	
	Character *player = new Character(1, 10, 10, 10, 10, 10, 10);
	SubjectCharacter *subChar = new SubjectCharacter(player);
	player->setName("HELLO WORLD");

	Map *map = new Map(1, 5, 5, player);
	SubjectMap *subMap = new SubjectMap(map);

	Game *game = new Game(5, 5, map);
	SubjectGame *subGame = new SubjectGame(game);

	char showDice, showChar, showMap, showGame;

	cout << "\nWould you like to see the DICE log?(y/n) ";
	cin >> showDice;

	cout << "\nWould you like to see the CHARACTER log?(y/n) ";
	cin >> showChar;

	cout << "\nWould you like to see the MAP log?(y/n) ";
	cin >> showMap;

	cout << "\nWould you like to see the GAME log?(y/n) ";
	cin >> showGame;

	if (showDice == 'n') {
		subDice->logDice();
	}
	if (showChar == 'n') {
		subChar->logCharacter();
	}
	if (showMap == 'n') {
		subMap->logMap();
	}
	if (showGame == 'n') {
		subGame->logGame();
	}

	// will print out roll and logs data on roll
	cout << "\n[Dice Roll log]" << endl;
	dice->roll("1d6[0]");
	dice->roll("2d10[10000]");
	dice->roll("3d20[100000]");
	dice->roll("4d20[100000]");
	dice->roll("20d100[10000000]");

	// player attacts with damage, logs out damage with modifiers
	cout << "\n[Player attacks log]" << endl;
	player->attack(10);
	player->attack(200);
	player->attack(3000);
	player->attack(40000);
	player->attack(500000);

	cout << "\n[Player movement log]" << endl;
	// obsever notifies when character moves on map
	// setting new player position and telling map a new turn occurs mirrors ingame action
	map->nextTurn();
	
	player->setPosition(1, 1);
	map->nextTurn();
	
	player->setPosition(2, 2);
	map->nextTurn();

	player->setPosition(3, 3);
	map->nextTurn();


	int k;
	cin >> k;
}