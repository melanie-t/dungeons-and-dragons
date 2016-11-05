#include <iostream>
#include <string>
#include "FileMapBuilder.h"
#include "Door.h"
#include "Markup.h"
#include "WaterTexture.h"
#include "TreeTexture.h"
#include "BrickTexture.h"
#include "Item.h"
using namespace std;

void FileMapBuilder::loadMap(int id)
{
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
			Map* map = new Map(id);

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
						}
						door.setDestinationID(mapid);
						map->fillCell(x, y, door);
						xml.OutOfElem();
					}
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
					cout << "items" << endl;
					xml.IntoElem();
					int x, y;
					Item item = Item::randommize(1); // temp get character level.
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
					map->fillCell(x, y, item);
					xml.OutOfElem();
				}
				else if (s == "enemies")
				{
					cout << "hi yall" << endl;
					xml.IntoElem();
					while (xml.FindElem())
					{
						std::cout << "enemy" << endl;
						xml.IntoElem();
						//now in each enemy tage
						while (xml.FindElem())
						{
							std::cout << xml.GetTagName() << endl;
						}
						xml.OutOfElem();
					}
					xml.OutOfElem();
				}
			}
		}
	}
	else
	{
		cout << xml.GetError() << endl;
	}
}