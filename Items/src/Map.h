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
#include "GameObject.h"
#include "Character.h"
#include <vector>

#ifndef Map_H
#define Map_H
class Map {
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
	void printMap(char** map, int length, int width);
	void setElement(char** map, int row, int column, char element);
	void createMapSize(int x, int y);
	vector<int> outputMap();
	bool inputMap(vector<int> arrayIn); 
	bool saveMap();

	//Getters
	int getID(){ return this->ID; }
	std::string getName(){ return this->name; }
	int getNumRows(){ return this->row; }
	int getNumCol(){ return this->column; }
	(GameObject*)** getMap(){ return this->map; }
	Character* getPlayer(){ return this->player; }

	//setters
	void setID(int id){ this->ID = id; }
	void setName(std::string name){ this->name = name; }
	void setNumRows(int rows){ this->row = rows; }
	void setNumCol(int col){ this->column = col; }
private:
	//Member variables;
	//grass, tree, water, brick.
	GameObject*** map;
	int row;
	int column;
	int ID;
	std::string name;
	int** mapSearch;
	bool recursiveSearch(int posx, int posy, int endposx, int endposy);
	Character* player;
};
#endif
