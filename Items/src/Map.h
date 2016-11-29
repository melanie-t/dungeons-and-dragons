//! @file 
//! @brief Header file for the Map class  
//!
//! There's no additional game rules at play in these files that haven't already
//! been implements. The Map Class,the character class and the Item class
//! all check to see if the created maps are valid.
//! we allow doors to be anywhere, no known restrictions that disallow doors
//! to be in the middle of the map in the d20 rules.
//!

#pragma once

#include <iostream>
#include <string>
#include <map>
#include "GameObject.h"
#include "Character.h"
#include "Enemy.h"
#include "Friend.h"
#include <vector>
#include "pos.h"

class Map 
{
public:
	//Constructor
	Map(const int id, const int length = 20, const int width = 20, Character* player = nullptr);
	Map();

	//Destructor
	~Map();

	//Methods
	bool validatePath();
	void fillCell(int x, int y, GameObject* obj);
	bool isOccupied(int x, int y);
	void setElement(char** map, int row, int column, char element);
	void createMapSize(int x, int y);
	vector<int> outputMap();
	bool saveMap();
	void printMap();

	//Getters
	int getID(){ return this->ID; }
	std::string getName(){ return this->name; }
	int getWidth(){ return this->width; }
	int getLength(){ return this->length; }
	(GameObject*)** getMap(){ return this->map; }
	Character* getPlayer(){ return this->player; }
	GameObject* getObject(int x, int y);
	std::vector<pos> getDoors(){ return doors;  }
	std::vector<Enemy*> getEnemies(){ return enemies; }
	std::vector<Friend*> getFriends(){ return friends; }
	Enemy* getClosestEnemy(Character* origin);
	void removeEnemy(Enemy* enemy);
	void removeFriend(Friend* frien);

	//setters
	void setID(int id){ this->ID = id; }
	void setName(std::string name){ this->name = name; }
	void setWidth(int wid){ this->width = wid; }
	void setLength(int len){ this->length = len; }

	void nextTurn();
	Character* getTurn();
	Character* getCharacterAt(int x, int y);
private:
	//Member variables;
	//grass, tree, water, brick.
	GameObject*** map;
	int width;
	int length;
	int ID;
	int turn;
	std::string name;
	std::vector<pos> doors;
	int** mapSearch;
	bool recursiveSearch(int posx, int posy, int endposx, int endposy);
	vector<Enemy*> enemies;
	vector<Friend*> friends;
	vector<Character*> turns;
	Character* player;
};
