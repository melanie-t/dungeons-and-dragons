
#pragma once
#include <iostream>
#include <string>

#ifndef Map_H
#define Map_H
class Map {
public:
	//Constructor
	Map(const int id, const int length, const int width, const std::string name);
	bool validatePath();
	void fillCell(int x, int y, char obj);
	bool isOccupied(int x, int y);
	void printMap(char** map, int length, int width);
	void setElement(char** map, int row, int column, char element);
private:
	// Char constants to create the elements within the maps
	static const char WALL = '#';
	static const char PLAYER = 'x';
	static const char ENEMY = 'y';
	static const char ITEM = '!';
	static const char DOOR = '|';
	static const char SPACE = ' ';
	static const char START = 'S';
	static const char EXIT = 'E';
	//Member variables;
	char** map;
	int row;
	int column;
	int ID;
	std::string name;
	int** mapSearch;
	bool recursiveSearch(int posx, int posy, int endposx, int endposy);
};
#endif
