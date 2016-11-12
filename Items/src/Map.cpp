/*
This class is the map class that creates an 2 dimensional array game map
The map is designed as a grid, where each cell is either
1)Empty cell where character can move
2)Wall where character cannot move
3)Occupied cell containing character, opponent, chest, door, etc.

The map can also be a blank map,
However, the map needs a path between the begin cell and end cell.

*/
//! @file 
//! @brief Implementation file for the Map class  
//!
#include <iostream>
#include "Map.h"
#include <vector>
#include "Character.h"
#include "Door.h"
#include "Markup.h"
using namespace std;

//! Default Constructor
//! Sets everything to 0, or empty string.
Map::Map()
{
	Map(0, 0, 0, nullptr);
}
//! Constructor method for the map.
//! @param is the id of the map
//! @param length the length of the map
//! @param width the width of the map
//! @param name the name of the map
Map::Map(const int id, const int length, const int width, Character* player)
{
	this->ID = id;
	//width = row, length = column
	this->row = width;
	this->column = length;
	//Player on the map.
	this->player = player;
	//Creating an array that will serve as our map.
	map = new GameObject**[width];
	for (int i = 0; i < width; ++i){
		map[i] = new GameObject*[length];
	}

	for (int i = 0; i < width; ++i){
		for (int j = 0; j < length; ++j){
			map[i][j] = new GameObject();
		}
	}

	//Creating an array in order to search it.
	mapSearch = new int*[width];
	for (int i = 0; i < length; ++i)
		mapSearch[i] = new int[length];
}
//! destructor of the map class
//! @brief deletes the player with the map.
Map::~Map()
{
	if (player != nullptr) delete player;
}
//! printMap function
//! Method to print the map array
void Map::printMap(char** map, int length, int width)
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; i++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
}
//! setElement function
//! Method to set an element in the array (in order to create the map)
void Map::setElement(char** map, int row, int column, char element)
{
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
//! validatePath function
//! checks if there's a valid path
//! between the start point and the end point
bool Map::validatePath()
{
	bool startpoint = false;
	bool endpoint = false;
	int startx, starty;
	int endx, endy;
	//check if there's a start point and end point
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < column; ++j) {
			if (map[i][j]->getObjectType() == DOOR)
			{
				if (i != 0 && j != 0 && i != row - 1 && j != column - 1)
				{
					//The door is not at the egde of the map.
					return false;
				}
				Door* door = static_cast<Door*> (map[i][j]);

				if (door->getStart()) { //start
					startpoint = true;
					startx = i;
					starty = j;
				}
				if (!door->getStart()) { // end
					endpoint = true;
					endx = i;
					endy = j;
				}
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
//! fillCell function
//! fill the cell with a GameObject
//! @param obj the GameObject to fill the cell with.
void Map::fillCell(int x, int y, GameObject* obj)
{

	if (x > row || y > column)
	{
		cout << "invalid position" << endl;
		return;
	}

	map[x][y] = obj;
}
//! isOccupied function
//! Checks to see if the cell is occupied
//! @param x the x coordinate of the cell.
//! @param y the y coordinate of the cell.
bool Map::isOccupied(int x, int y)
{
	if (map[x][y]->getObjectType() == "") {
		return false;
	}
	else
		return true;
}
//! recursiveSearch function
//! recurive search...
bool Map::recursiveSearch(int posx, int posy, int endposx, int endposy)
{
	//Current position is the end position.
	GameObject* cur = map[posx][posy];
	GameObject* end = map[endposx][endposy];
	
	//cur and end point to the same reference,
	//therefore, they're the same object.
	if (cur == end) {
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

vector<int> Map::outputMap()
{
	vector<int> output;
	for (int i = 0; i != this->column; i++)
	{
		for (int j = 0; j != this->row; j++)
		{
			if (map[i][j]->getObjectType() == WATER)
			{
				output.push_back(1); // idk what these are supposed to push.
			}
			else if (map[i][j]->getObjectType() == TREE)
			{
				output.push_back(2); // idk what these are supposed to push.
			}
			else if (map[i][j]->getObjectType() == DOOR)
			{
				if (static_cast<Door*>(map[i][j])->getStart())
				{
					output.push_back(7);
				}
				else
				{
					output.push_back(6); // idk what these are supposed to push.
				}
			}
			else if (map[i][j]->getObjectType() == ITEM)
			{
				output.push_back(9);
			}
			else if (map[i][j]->getObjectType() == ENEMY)
			{
				output.push_back(10);
			}
			else
			{
				output.push_back(0); //idk what these are supposed to be, (get grass graphics)
			}
		}
	}
	return output;
}

//takes the 1D array from the editor and turns it into a new map object
//because we make new objects all the time will we run out of mem....
bool Map::inputMap(vector<int>arrayIn){
	cout << "\nNew Map length::" << row << endl;
	cout << "New Map Height::" << column<< endl;
	cout << "arrayInSIZE: " << arrayIn.size() << endl;
	int type = 0;
	int x, y;
	for (int i = 0; i < arrayIn.size(); i++){
		
		type = arrayIn[i];
		switch (type){
		case 1:{		//water
			x = i % row;
			y = i / row;
			map[x][y]->setObjectType(WATER);
			break;
		}
		case 2:{		//tree
			x = i % row;
			y = i / row;
			map[x][y]->setObjectType(TREE);
			break;
		}
		case 7:{		//door
			x = i % row;
			y = i / row;
			map[x][y]->setObjectType(DOOR);
			break;
		}
		case 9:{		//item
			x = i % row;
			y = i / row;
			map[x][y]->setObjectType(ITEM);
			break;
		}
		case 10:{		//enemy
			x = i % row;
			y = i / row;
			map[x][y]->setObjectType(ENEMY);
			break;
		}
		}
	}
	cout << "\nFinished converting array to XML" << endl;

	//saves XML to disk
	saveMap();
	return true;

	// map validation doesn't work properly
	/*
	if (validatePath()){
		cout << "Map Validated! \nSaving map..." << endl;
		saveMap();
		return true;
	}
	else{
		cout << "Validation failed. \nMap not saving." << endl;
		return false;
	}
	cout << "The map was unable to save." << endl;
	*/
}

bool Map::saveMap()
{
	//map validation doesn't work properly
	/*
	if (validatePath() == false)
	{
		//Invalid Map.
		return false;
	}
	*/

	CMarkup xml;
	xml.AddElem("map");
	xml.IntoElem();
	xml.AddElem("id", this->ID);
	xml.AddElem("rows", this->row);
	xml.AddElem("column", this->column);

	xml.SavePos("map");

	for (int i = 0; i != this->column; i++)
	{
		for (int k = 0; k != this->row; k++)
		{
			if (&this->map[i][k] == nullptr)
			{
				continue;
			}
			else
			{
				if (this->map[i][k]->getObjectType().empty()) continue;

				if (this->map[i][k]->getObjectType() == ITEM)
				{
					if (!xml.FindElem("items"))
					{
						xml.AddElem("items");
					}
					xml.IntoElem();
					xml.AddElem("item");
					xml.IntoElem();
					xml.AddElem("x", i);
					xml.AddElem("y", k);
					xml.RestorePos("map");
				}
				else if (this->map[i][k]->getObjectType() == DOOR)
				{
					if (!xml.FindElem("doors"))
					{
						xml.AddElem("doors");
					}
					xml.IntoElem();
					xml.AddElem("door");
					xml.IntoElem();

					Door* door = static_cast<Door*>(map[i][k]);
					xml.AddElem("mapid", door->getDestinationID());
					xml.AddElem("x", i);
					xml.AddElem("y", k);
					xml.AddElem("start", door->getStart());
					xml.RestorePos("map");
				}
				else if (this->map[i][k]->getObjectType() == WATER)
				{
					if (!xml.FindElem("walls"))
					{
						xml.AddElem("walls");
					}
					xml.IntoElem();
					xml.AddElem("wall");
					xml.IntoElem();

					xml.AddElem("type", "water");
					xml.AddElem("x", i);
					xml.AddElem("y", k);
					xml.RestorePos("map");
				}
				else if (this->map[i][k]->getObjectType() == TREE)
				{
					if (!xml.FindElem("walls"))
					{
						xml.AddElem("walls");
					}
					xml.IntoElem();
					xml.AddElem("wall");
					xml.IntoElem();

					xml.AddElem("type", "tree");
					xml.AddElem("x", i);
					xml.AddElem("y", k);
					xml.RestorePos("map");
				}
				else if (this->map[i][k]->getObjectType() == BRICK)
				{
					if (!xml.FindElem("walls"))
					{
						xml.AddElem("walls");
					}
					xml.IntoElem();
					xml.AddElem("wall");
					xml.IntoElem();

					xml.AddElem("type", "brick");
					xml.AddElem("x", i);
					xml.AddElem("y", k);
					xml.RestorePos("map");
				}
				else if (this->map[i][k]->getObjectType() == ENEMY)
				{
					if (!xml.FindElem("enemies"))
					{
						xml.AddElem("enemies");
					}
					xml.IntoElem();
					xml.AddElem("enemy");
					xml.IntoElem();

					xml.AddElem("x", i);
					xml.AddElem("y", k);
					xml.RestorePos("map");
				}
			}
		}
	}
	char di[20];
	sprintf_s(di, 20, "maps/%d.xml", ID);
	xml.Save(string(di));
	cout << "The map has been saved!";
	return true;
}

