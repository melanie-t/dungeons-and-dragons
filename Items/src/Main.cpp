#include "Game.h"
#include "FileMapBuilder.h"
#include "SavedMapBuilder.h"
#include "Character.h"
#include "Enemy.h"
#include "Door.h"
#include "Item.h"
#include "Markup.h"
#include <thread>
#include <Windows.h>
using namespace std;


/**
Console input thread.
Take commands through the console. Temporary.
*/
void runGame(int chosenMap, string characterName)
{
	Character* character = Character::loadCharacer(characterName);
	character->setName(characterName);

	FileMapBuilder builder(character);
	builder.loadMap(chosenMap);
	Map* map = builder.getMap();

	Game* game = new Game(map->getNumRows(), map->getNumCol(), map);

	try{
		game->go();
		system("pause");
	}
	catch (char* e){
		MessageBoxA(NULL, e, "EXCEPTION OCCURED", MB_OK | MB_ICONERROR);
	}
}

/**
Main function.
*/
int main()
{

	cout << "Welcome To Our Dnd demo!" << endl;

	bool run = true;
	bool gameRunning = false;
	while (run)
	{
		cout << "What would you like to do? (enter number)" << endl;
		cout << "1. Start game" << endl;
		cout << "2. Create/Edit Map" << endl;
		cout << "3. Create/Edit Character" << endl;
		cout << "4. Create/Edit Item" << endl;
		cout << "5. Exit program" << endl;
		int cmd;
		cin >> cmd;

		if (gameRunning && cmd == 1)
		{
			cin >> cmd;
		}

		switch (cmd)
		{
		case 1: // Start game
		{
			/*if (!gameRunning)
			{
				string name;
				std::cout << "Enter Character Name: " << endl;
				cin >> name;

				cout << "Choose a map id from the list below:" << endl;

				int id = 1;
				CMarkup xml;
				char di[20];
				sprintf_s(di, 20, "maps/%d.xml", id);

				while (xml.Load(di))
				{
				cout << id << endl;
				id++;
				sprintf_s(di, 20, "maps/%d.xml", id);
				}

				int chosenMap;
				cin >> chosenMap;

				gameRunning = true;

				std::thread consoleThread(runGame, chosenMap, name);
				consoleThread.join();
			}
			else
			{
				cout << "Error: Game is already running." << endl;
			}*/
			break;
			//Move stuff
		} // Start Game FIN
		case 2: // Create/Edit map 
		{
			bool mapedit = true;
			while (mapedit)
			{
				cout << "What would you map editing function would you like to do? (enter number)" << endl;
				cout << "1. Create Map" << endl;
				cout << "2. Edit Map" << endl;
				cout << "3. Exit Map Editor" << endl;
				int  map_cmd;
				std::cin >> map_cmd;
				Map* map = nullptr;
				switch (map_cmd)
				{
				case 1: // create map:
				{
					int width, length;
					cout << "What length should the map be?" << endl;
					cin >> length;
					cout << "What width should the map be?" << endl;
					cin >> width;
					//map = new Map();

					//find a better way of doing this.
					int id = 1;
					CMarkup xml;
					char di[20];
					sprintf_s(di, 20, "maps/%d.xml", id);
					while (xml.Load(string(di)))
					{
						id++;
						sprintf_s(di, 20, "maps/%d.xml", id);
					}
					map = new Map(id, length, width);
					cout << "Created new map with ID: " << id << endl;
					break;
				}
				case 2: //edit map
				{
					int id = -1;
					SavedMapBuilder builder;

					do
					{
						cout << "Enter the map id of the map you want to edit: " << endl;
						cin >> id;
					} while (!builder.loadMap(id));

					map = builder.getMap();
					break;
				}
				case 3: // exit 
				{
					mapedit = false;
					break;
				}
				}

				if (map != nullptr)
				{
					bool changeMap = true;
					while (changeMap)
					{
						cout << "What would you like to do with the map?" << endl;
						cout << "1. Add Door" << endl;
						cout << "2. Add Item" << endl;
						cout << "3. Add Enemy" << endl;
						cout << "4. Exit & Save" << endl;
						cout << "5. Exit & Don't Save" << endl;
						int editcmd;
						cin >> editcmd;

						int x, y;
						if (editcmd != 4 && editcmd != 5)
						{
							do
							{
								cout << "Enter x position: ";
								cin >> x;
								cout << "Enter y position: ";
								cin >> y;
							} while (x > map->getNumRows() || x < 0 || y > map->getNumRows() || y < 0);
						}

						switch (editcmd)
						{
						case 1: //add door.
						{
							int mapid;
							bool start;
							cout << "Enter mapid that the door leads to: ";
							cin >> mapid;
							cout << "Is this a start or end position(1 for start, 0 for end): ";
							cin >> start;
							map->fillCell(x, y, new Door(mapid, start));
							break;
						}
						case 2: // add item in this area
						{
							map->fillCell(x, y, new Item());
							break;
						}
						case 3: //add enemy in this area
						{
							map->fillCell(x, y, new Enemy());
							break;
						}
						case 4: // exit + save, no break function
						{
							map->saveMap();
						}
						case 5: //exit without saving.
						{
							changeMap = false;
							break;
						}
						default:
							cout << "Unknown Command" << endl;
						}
					}
				}
			}
		} // Map FIN
		case 3: // Create/Edit Character
		{

		} // Character FIN

		case 4: // Create/Edit Item
		{

		} // Item FIN

		case 5: // Exit
		{
			run = false;
		}
		} // Switch Menu FIN
	}
	///////////////////////
}