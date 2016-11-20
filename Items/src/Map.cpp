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
#include "TileTypes.h"
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
	//length, width
	this->width = width;
	this->length = length;
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
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < length; ++j) {
			if (map[i][j]->getObjectType() == OBJ_DOOR)
			{
				/*if (i != 0 && j != 0 && i != row - 1 && j != column - 1)
				{
					//The door is not at the egde of the map.
					return false;
				}*/
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

	if (x > width || y > length)
	{
		cout << "invalid position" << endl;
		return;
	}

	if (obj->getObjectType() == OBJ_DOOR)
	{
		pos position;
		position.x = x;
		position.y = y;
		
		doors.push_back(position);
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
	else if (posx < 0 || posy < 0 || posx > width || posy > length) {
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

//! outputMap function
//! @brief outputs the map as a 1D array to be used for gui tiles.
vector<int> Map::outputMap()
{
	vector<int> output;
	for (int i = 0; i != this->length; i++)
	{
		for (int j = 0; j != this->width; j++)
		{
			if (map[i][j]->getObjectType() == OBJ_WATER)
			{
				output.push_back(TileTypes::WATER);
			}
			else if (map[i][j]->getObjectType() == OBJ_TREE)
			{
				output.push_back(TileTypes::TREE);
			}
			else if (map[i][j]->getObjectType() == OBJ_DOOR)
			{
				if (static_cast<Door*>(map[i][j])->getStart())
				{
					output.push_back(TileTypes::START);
				}
				else
				{
					output.push_back(TileTypes::END); 
				}
			}
			else if (map[i][j]->getObjectType() == OBJ_CHEST)
			{
				output.push_back(TileTypes::CHEST);
			}
			else if (map[i][j]->getObjectType() == OBJ_ENEMY)
			{
				output.push_back(TileTypes::ENEMY);
			}
			else if (map[i][j]->getObjectType() == OBJ_FRIEND)
			{
				output.push_back(TileTypes::FRIEND);
			}
			else
			{
				output.push_back(TileTypes::GRASS);
			}
		}
	}
	return output;
}

//! saveMap function
//! @brief Saves the map object into an xml file.
bool Map::saveMap()
{
	if (!this->validatePath())
	{
		//Invlaid map.
		return false;
	}

	CMarkup xml;
	xml.AddElem("map");
	xml.IntoElem();
	xml.AddElem("id", this->ID);
	xml.AddElem("width", this->width);
	xml.AddElem("column", this->length);

	xml.SavePos("map");

	for (int i = 0; i != this->length; i++)
	{
		for (int k = 0; k != this->width; k++)
		{
			if (&this->map[i][k] == nullptr)
			{
				continue;
			}
			else
			{
				if (this->map[i][k]->getObjectType().empty()) continue;

				if (this->map[i][k]->getObjectType() == OBJ_CHEST)
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
				else if (this->map[i][k]->getObjectType() == OBJ_DOOR)
				{
					if (!xml.FindElem("doors"))
					{
						xml.AddElem("doors");
					}
					xml.IntoElem();
					xml.AddElem("door");
					xml.IntoElem();

					Door* door = static_cast<Door*>(map[i][k]);
					//xml.AddElem("mapid", door->getDestinationID());
					xml.AddElem("x", i);
					xml.AddElem("y", k);
					xml.AddElem("start", door->getStart());
					xml.RestorePos("map");
				}
				else if (this->map[i][k]->getObjectType() == OBJ_WATER)
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
				else if (this->map[i][k]->getObjectType() == OBJ_TREE)
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
				else if (this->map[i][k]->getObjectType() == OBJ_BRICK)
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
				else if (this->map[i][k]->getObjectType() == OBJ_ENEMY)
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
				else if (this->map[i][k]->getObjectType() == OBJ_FRIEND)
				{
					if (!xml.FindElem("friends"))
					{
						xml.AddElem("friends");
					}
					xml.IntoElem();
					xml.AddElem("friend");
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
	return xml.Save(string(di));
}
//! printMap function
//! Method to print the map array
void Map::printMap()
{
	cout << "Map: " << endl << endl;
	cout << "C: Chest" << endl;
	cout << "G: Grass" << endl;
	cout << "M: Enemy" << endl;
	cout << "W: Water" << endl;
	cout << "T: Tree" << endl;
	cout << "S: Start Door" << endl;
	cout << "E: End Door" << endl;
	cout << "F: Friendly NPC" << endl;

	cout << endl << endl; //skip two lines.

	for (int i = 0; i != this->getLength(); i++)
	{
		for (int k = 0; k != this->getWidth(); k++)
		{
			if (this->map[i][k]->getObjectType() == OBJ_CHEST)
			{
				cout << "C ";
			}
			else if (this->map[i][k]->getObjectType() == OBJ_ENEMY)
			{
				cout << "M ";
			}
			else if (this->map[i][k]->getObjectType() == OBJ_FRIEND)
			{
				cout << "F ";
			}
			else if (this->map[i][k]->getObjectType() == OBJ_WATER)
			{
				cout << "W ";
			}
			else if (this->map[i][k]->getObjectType() == OBJ_TREE)
			{
				cout << "T ";
			}
			else if (this->map[i][k]->getObjectType() == OBJ_DOOR)
			{
				if (static_cast<Door*>(this->map[i][k])->getStart())
				{
					cout << "S ";
				}
				else
				{
					cout << "E ";
				}
			}
			else
			{
				cout << "G "; //Grass
			}
		}
		cout << endl;
	}
	cout << endl;
}

GameObject* Map::getObject(int x, int y)
{
	return map[y][x];
}

