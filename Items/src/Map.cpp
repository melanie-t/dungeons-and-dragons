/*
This class is the map class that creates an 2 dimensional array game map
The map is designed as a grid, where each cell is either
1)Empty cell where character can move
2)Wall where character cannot move
3)Occupied cell containing character, opponent, chest, door, etc.

The map can also be a blank map,
However, the map needs a path between the begin cell and end cell.

*/
#include <iostream>
#include "Map.h"
#include <vector>
#include "Character.h"
using namespace std;

	//Default Constructor
	Map::Map()
	{
		Map(0, 0, 0, "");
	}
	//Constructor method for the map.
	Map::Map(const int id, const int length, const int width, const string name, Character* player)
	{
		this->ID = id;
		//width = row, length = column
		this->row = width;
		this->column = length;
		this->name = name;
		//Player on the map.
		this->player = player;
		//Creating an array that will serve as our map.
		map = new GameObject*[width];//= new char*[width];
		for (int i = 0; i < length; ++i)
			map[i] = new GameObject[length];
		//Creating an array in order to search it.
		mapSearch = new int*[width];
		for (int i = 0; i < length; ++i)
			mapSearch[i] = new int[length];
	}
	//Method to print the map array
	void Map::printMap(char** map, int length, int width) {
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < width; i++)
			{
				cout << map[i][j];
			}
			cout << endl;
		}
	}
	//Method to set an element in the array (in order to create the map)
	void Map::setElement(char** map, int row, int column, char element) {
		for (int i = 0; i <= row; i++) {
			if (i == row) {
				for (int j = 0; j <= column; j++) {
					if (j == column) {
						map[i][j] = element;
					}
				}
			}
		}
	}
	bool Map::validatePath() {
		bool startpoint = false;
		bool endpoint = false;
		int startx, starty;
		int endx, endy;
		//check if there's a start point and end point
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < column; ++j) {
				if (map[i][j].getObjectType() == "S") {
					startpoint = true;
					startx = i;
					starty = j;
				}
				if (map[i][j].getObjectType() == "E") {
					endpoint = true;
					endx = i;
					endy = j;
				}
			}
		}
		//if there is a starpoint and endpoint, then you can check if there is a valid path on the map. 
		if (startpoint && endpoint) {
			return recursiveSearch(startx, starty, endx, endy);
		}
		else {
			return false;
		}
	}
	void Map::fillCell(int x, int y, GameObject obj) {

		if (x > row || y > column)
		{
			cout << "invalid position" << endl;
			return;
		}

		map[x][y] = obj;
	}
	bool Map::isOccupied(int x, int y) {
		if (&map[x][y] == nullptr) {
			return false;
		}
		else
			return true;
	}
	bool Map::recursiveSearch(int posx, int posy, int endposx, int endposy) {
		//Current position is the end position.
		GameObject cur = map[posx][posy];
		GameObject end = map[endposx][endposy];
		///Need to double check. Should work, I think. compares address.
		if (&cur == &end) { 
			return true;
		}
		//find a way to keep track of where ive already visited.
		else if (mapSearch[posx][posy]) { //Check if the flag is on, on that posx and posy in order to avoid infinite loop.
			return false;
		}
		else if (posx < 0 || posy < 0 || posx > row || posy > column) {
			return false;
		}
		else if (&map[posx][posy] == nullptr) {
			return false;
		}
		//Recursion to check down,up,left,right
		else{
			mapSearch[posx][posy] = 1; //turn the flag on
			return recursiveSearch(posx - 1, posy, endposx, endposy) || recursiveSearch(posx + 1, posy, endposx, endposy) || recursiveSearch(posx, posy - 1, endposx, endposy) || recursiveSearch(posx, posy + 1, endposx, endposy);
		}
	}

