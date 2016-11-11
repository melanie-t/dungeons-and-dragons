#include "Game.h"
#include "FileMapBuilder.h"
#include "SavedMapBuilder.h"
#include "Character.h"
#include "Fighter.h"
#include "Enemy.h"
#include "Door.h"
#include "Item.h"
#include "Markup.h"
#include <thread>
#include <Windows.h>
using namespace std;

std::thread runGameThread;
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
	}
	catch (char* e){
		MessageBoxA(NULL, e, "EXCEPTION OCCURED", MB_OK | MB_ICONERROR);
	}
	runGameThread.detach();
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
		cout << "1. Start/End game" << endl;
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
			if (!gameRunning)
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

				runGameThread = std::thread(runGame, chosenMap, name);
			}
			else
			{
				cout << "Error: Game is already running. Detatching thread..." << endl;
				runGameThread.detach();
				gameRunning = false;
			}
			break;
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
				} // end switch

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
							break;
						}
						case 5: //exit without saving.
						{
							changeMap = false;
							break;
						}
						default:
							cout << "Unknown Command" << endl;
							break;
						}
					}
				}
			}
			break;
		} // Map FIN
		case 3: // Create/Edit Character
		{
			bool characteredit = true;
			char save;
			while (characteredit)
			{
				cout << "What would you like to do?"
					<< "\n1. Create new character (Fighter)"
					<< "\n2. Edit character"
					<< "\n3. Exit to previous menu" << endl;
				int charactercmd;
				cin >> charactercmd;

				switch (charactercmd)
				{
				case 1: // create new character
				{
					string name;
					char decision;
					cout << "Enter name of your character: " << endl;
					cin >> name;
					Fighter newFighter(name);
					newFighter.notify();

					//Ask if player wants to save this character
					cout << "Do you want to save this Fighter (Y/N)?" << endl;
					cin >> decision;
					if (decision == 'Y' || decision == 'y')
					{
						newFighter.saveCharacter();
						cout << "Fighter " << name << " saved. Returning to menu.\n" << endl;
					}
					break;
				}
				case 2: // edit character
				{
					string name;
					int modifycmd;
					bool change = false;
					bool modifycontinue = true;

					cout << "Enter the name of the Fighter you want to edit: " << endl;
					cin >> name;
					Fighter* fighterPointer;
					fighterPointer = Fighter::loadFighter(name);

					// Select modifying category
					while (modifycontinue) {
						fighterPointer->notify();
						cout << "Which category do you wish to modify?"
							<< "\n1. STR (Strength)"
							<< "\n2. DEX (Dexterity)"
							<< "\n3. CON (Constitution)"
							<< "\n4. INT (Intelligence)"
							<< "\n5. WIS (Wisdom)"
							<< "\n6. CHA (Charisma)"
							<< "\n7. Name" 
							<< "\n8. Exit to previous menu" << endl;
						cin >> modifycmd;
						switch (modifycmd) {
						case 1: //STR
						{
							int value;
							cout << "Enter new STR value:" << endl;
							cin >> value;
							if (value >= 3 && value <= 18) {
								fighterPointer->setSTR(value);
								change = true;
							}
							else
								cout << "~ Invalid input ~ Ability must be between 3 and 18."
								<< " Please try again." << endl;
							break;
						}
						case 2: //DEX
						{
							int value;
							cout << "Enter new DEX value:" << endl;
							cin >> value;
							if (value >= 3 && value <= 18) {
								fighterPointer->setDEX(value);
								change = true;
							}
							else
								cout << "~ Invalid input ~ Ability must be between 3 and 18."
								<< " Please try again." << endl;
							break;
						}
						case 3: //CON
						{
							int value;
							cout << "Enter new CON value:" << endl;
							cin >> value;
							if (value >= 3 && value <= 18) {
								fighterPointer->setCON(value);
								change = true;
							}
							else
								cout << "~ Invalid input ~ Ability must be between 3 and 18."
								<< " Please try again." << endl;
							break;
						}
						case 4: //INT
						{
							int value;
							cout << "Enter new INT value:" << endl;
							cin >> value;
							if (value >= 3 && value <= 18) {
								fighterPointer->setINTEL(value);
								change = true;
							}
							else
								cout << "~ Invalid input ~ Ability must be between 3 and 18."
								<< " Please try again." << endl;
							break;
						} 
						case 5: //WIS
						{
							int value;
							cout << "Enter new WIS value:" << endl;
							cin >> value;
							if (value >= 3 && value <= 18) {
								fighterPointer->setWIS(value);
								change = true;
							}
							else
								cout << "~ Invalid input ~ Ability must be between 3 and 18."
								<< " Please try again." << endl;
							break;
						}
						case 6: //CHA
						{
							int value;
							cout << "Enter new CHA value:" << endl;
							cin >> value;
							if (value >= 3 && value <= 18) {
								fighterPointer->setCHA(value);
								change = true;
							}
							else
								cout << "~ Invalid input ~ Ability must be between 3 and 18."
								<< " Please try again." << endl;
							break;
						}
						case 7: //Name
						{
							string name;
							cout << "Enter new name:" << endl;
							cin >> name;
							fighterPointer->setName(name);
							change = true;
							break;
						}
						case 8: //Exit to previous menu
						{
							modifycontinue = false;
							break;
						}
						} // end modify character switch
					} //end modify ability while loop
					
					//Asks user to save stats if change has occured
					if (change) {
						cout << "Would you like to save your new stats (Y/N)?" << endl;
						cin >> save;
						if (save == 'Y' || save == 'y')
						{
							fighterPointer->saveCharacter();
							cout << "New stats saved" << endl;
						}
					}
					break;
				}
				case 3: // exit
				{
					characteredit = false;
					break;
				}
				} // end character switch
			} // end characteredit loop
			break;
		} // Character FIN

		case 4: // Create/Edit Item
		{
			bool itemedit = true;
			while (itemedit)
			{
				cout << "What would you like to do?"
					<< "\n1. Create new item"
					<< "\n2. Edit item"
					<< "\n3. Exit to previous menu" << endl;
				int itemcmd;
				cin >> itemcmd;

				switch (itemcmd)
				{
				case 1: // create new item
				{
					vector<Enhancement> enhance;
					int itemchoice;
					
					bool continueCreation = true;
					while (continueCreation)
					{
						cout << "What would you like to create?"
							<< "\n1. Helmet"
							<< "\n2. Armor"
							<< "\n3. Shield"
							<< "\n4. Ring"
							<< "\n5. Belt"
							<< "\n6. Boots"
							<< "\n7. Weapon"
							<< "\n8. Exit to previous menu" << endl;
						cin >> itemchoice;
					
						switch (itemchoice){
						case 1: // Helmet
						{
							Item newItem = Item("Helmet", enhance);
							break;
						}
						case 2: // Armor
						{
							break;
						}
						case 3: // Shield
						{
							break;
						}
						case 4: // Ring
						{
							break;
						}
						case 5: // Belt
						{
							break;
						}
						case 6: // Boots
						{
							break;
						}
						case 7: // Boots
						{
							break;
						}
						case 8: // Exit
						{
							continueCreation = false;
							break;
						}
						} // end of itemChoice switch
					} // while loop continue creation
					break;
				} // end case 1 (create item)
				case 2: // edit  item
				{
					break;
				}
				case 3: // exit to main menu
				{
					itemedit = false;
					break;
				}
				} //end item switch
			} //end item edit while loop
			break;
		} // Item FIN

		case 5: // Exit
		{
			run = false;
			break;
		}
		} // Switch Menu FIN
	}
	///////////////////////
}