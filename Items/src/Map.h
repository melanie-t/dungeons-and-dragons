
#pragma once
#include <iostream>
#include <string>
#include "GameObject.h"
#include "Character.h"

#ifndef Map_H
#define Map_H
class Map {
public:
	//Constructor
	Map(const int id, const int length = 20, const int width = 20, const std::string name = "", Character* player = nullptr);
	Map();

	//Destructor
	~Map();

	//Methods
	bool validatePath();
	void fillCell(int x, int y, GameObject obj);
	bool isOccupied(int x, int y);
	void printMap(char** map, int length, int width);
	void setElement(char** map, int row, int column, char element);
	void createMapSize(int x, int y);

	//Getters
	int getID(){ return this->ID; }
	std::string getName(){ return this->name; }
	int getNumRows(){ return this->row; }
	int getNumCol(){ return this->column; }
	GameObject** getMap(){ return this->map; }

	//setters
	void setID(int id){ this->ID = id; }
	void setName(std::string name){ this->name = name; }
	void setNumRows(int rows){ this->row = rows; }
	void setNumCol(int col){ this->column = col; }
private:
	//Member variables;
	//grass, tree, water, brick.
	GameObject** map;
	int row;
	int column;
	int ID;
	std::string name;
	int** mapSearch;
	bool recursiveSearch(int posx, int posy, int endposx, int endposy);
	Character* player;
};
#endif
