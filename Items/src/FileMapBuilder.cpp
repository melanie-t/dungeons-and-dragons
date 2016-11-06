#include <iostream>
#include <string>
#include "FileMapBuilder.h"
#include "Door.h"
#include "Markup.h"
#include "WaterTexture.h"
#include "TreeTexture.h"
#include "BrickTexture.h"
#include "Item.h"
#include "GrassTexture.h"
#include "Enemy.h"
using namespace std;

FileMapBuilder::FileMapBuilder() : FileMapBuilder(nullptr)
{
}
FileMapBuilder::FileMapBuilder(Character* character)
{
	this->player = character;
}
FileMapBuilder::~FileMapBuilder()
{
	delete player;
}
bool FileMapBuilder::loadMap(int id)
{
	//Fill every empty tile with grass.
	//Is there a way to avoid a n^2 function?
	//I don't think we can avoid interating through everything.
	Map*map = new Map(id);

	char di[20];
	sprintf_s(di, 20, "%d.xml", id);

	CMarkup xml;
	if (xml.Load(string(di)))
	{
		xml.FindElem();

		if (xml.GetTagName() != "map")
		{
			cout << "This file is not a map." << endl;
			cout << xml.GetTagName() << endl;
		}
		else
		{
			xml.IntoElem();
			while (xml.FindElem())
			{
				string s = xml.GetTagName();
				if (s == "id")
				{
					map->setID(atoi(xml.GetData().c_str()));
				}
				else if (s == "rows")
				{
					map->setNumRows(atoi(xml.GetData().c_str()));
				}
				else if (s == "columns")
				{
					map->setNumCol(atoi(xml.GetData().c_str()));
				}
				else if (s == "doors")
				{
					xml.IntoElem();
					while (xml.FindElem())
					{
						Door door = Door();
						int x, y, mapid;
						bool start;

						xml.IntoElem();
						while (xml.FindElem())
						{
							string doorTag = xml.GetTagName();

							if (doorTag == "mapid")
							{
								mapid = atoi(xml.GetData().c_str());
							}
							else if (doorTag == "x")
							{
								x = atoi(xml.GetData().c_str());
							}
							else if (doorTag == "y")
							{
								y = atoi(xml.GetData().c_str());
							}
							else if (doorTag == "start")
							{
								start = (atoi(xml.GetData().c_str()) == 1);
							}
						}
						door.setDestinationID(mapid);
						door.setStart(start);
						map->fillCell(x, y, door);
						xml.OutOfElem();
					}
					xml.OutOfElem();
				}
				else if (s == "walls")
				{
					xml.IntoElem();
					while (xml.FindElem())
					{
						xml.IntoElem();
						string type;
						int x, y;
						GameObject wall;
						while (xml.FindElem())
						{
							if (xml.GetTagName() == "type")
							{
								type = xml.GetData().c_str();
							}
							else if (xml.GetTagName() == "x")
							{
								x = atoi(xml.GetData().c_str());
							}
							else if (xml.GetTagName() == "y")
							{
								y = atoi(xml.GetData().c_str());
							}
						}

						//Set proper subclass based on type of wall.
						if (type == "water")
						{
							wall = WaterTexture();
						}
						else if (type == "tree")
						{
							wall = TreeTexture();
						}
						else if (type == "brick")
						{
							wall = BrickTexture();
						}

						map->fillCell(x, y, wall);
						xml.OutOfElem();
					}
					xml.OutOfElem();
				}
				else if (s == "items")
				{
					xml.IntoElem();
					while (xml.FindElem())
					{
						xml.IntoElem();
						int x, y;
						Item item = Item::randommize(player->getLevel());
						while (xml.FindElem())
						{
							if (xml.GetTagName() == "x")
							{
								x = atoi(xml.GetData().c_str());
							}
							else if (xml.GetTagName() == "y")
							{
								y = atoi(xml.GetData().c_str());
							}
						}
						xml.OutOfElem();
						map->fillCell(x, y, item);
					}
					xml.OutOfElem();
				}
				else if (s == "enemies")
				{
					xml.IntoElem();
					while (xml.FindElem())
					{
						xml.IntoElem();
						Enemy enemy = Enemy::randomize(player);
						int x, y;
						//now in each enemy tage
						while (xml.FindElem())
						{
							if (xml.GetTagName() == "x")
							{
								x = atoi(xml.GetData().c_str());
							}
							else if (xml.GetTagName() == "y")
							{
								y = atoi(xml.GetData().c_str());
							}
						}
						map->fillCell(x, y, enemy);
						xml.OutOfElem();
					}
					xml.OutOfElem();
				}
			}

			for (int i = 0; i != map->getNumRows(); i++)
			{
				for (int k = 0; k != map->getNumCol(); k++)
				{
					if (!map->isOccupied(i, k))
					{
						map->fillCell(i, k, GrassTexture());
					}
				}
			}

			this->m_Map = map;
			return true;
		}
		return false;
	}
	else
	{
		cout << xml.GetError() << endl;
		return false;
	}
	return false;
}