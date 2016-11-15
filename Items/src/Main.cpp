#include "Game.h"
#include "FileMapBuilder.h"
#include "SavedMapBuilder.h"
#include "Character.h"
#include "Fighter.h"
#include "Enemy.h"
#include "Door.h"
#include "Item.h"
#include "Markup.h"
#include "Editor.h"
#include <thread>
#include <Windows.h>
#include <exception>
using namespace std;


std::thread runGameThread;
/**
Console input thread.
Take commands through the console. Temp
*/
void runGame(int chosenMap, string characterName)
{
	Character* character = Character::loadCharacer(characterName);
	character->setName(characterName);

	FileMapBuilder builder(character);
	builder.loadMap(chosenMap);
	Map* map = builder.getMap();

	Game* game = new Game(map->getNumRows(), map->getNumCol(), map);
	ItemPanel::createInventories();

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
				std::cout << "Choose a Fighter from the list."
					<< "\nDylan, James, Lisa, Maggie: "
					<< endl;
				cin >> name;
				if (name != "Dylan" && name != "James" && name != "Lisa" && name != "Maggie")
				{
					cout << "Invalid name entered. Playing as Dylan!" << endl;
					name = "Dylan";
				}
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
				cout << "4. GUI editor" << endl;
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
				}
				case 4: // TEST
				{
					
					cout << "\nWould you like to edit an existing map? (y/n): ";
					int editorWidth, editorHeight,choice;
					char editExisting;
					cin >> editExisting;

					if (editExisting == 'y'){
						//load a character to load map with... maybe create a generic character
						Character* character = Character::loadCharacer("james");
						character->setName("james");
						FileMapBuilder builder(character);
						
						cout << "\nPlease select a map to edit" << endl;
						cin >> choice;

						//find a better way of doing this.
						int id = 1;
						CMarkup xml;
						char di[20];
						sprintf_s(di, 20, "maps/%d.xml", id);
						while (xml.Load(string(di)))
						{
							cout << id << ".xml"<<endl;
							id++;
							sprintf_s(di, 20, "maps/%d.xml", id);
						}

						//load map of choice
						cout << "loading map" << endl;
						builder.loadMap(choice);
						Map* map = builder.getMap();
						
						//set editor to map dimensions
						editorWidth = map->getNumCol();
						editorHeight = map->getNumRows();

						//initialize editor
						Editor editor = Editor(editorWidth,editorHeight);

						// opens the editor with the previous map data
						cout << "starting editor" << endl;
						editor.initEditor(map);

						//saves map data into 1D array
						vector<int> newMap(editor.editorLoop());
						editor.close();

						cout << "\nwould you like to save the newly edited map [" << choice<<"] ?(y/n)" << endl;
						char saveMap;
						cin >> saveMap;

						if (saveMap == 'y'){
							//initialize map object to save map
							Map* mapToDisk = new Map(choice, editorWidth, editorHeight);

							//convert map array to xml and save to disk
							mapToDisk->inputMap(newMap);
						}

						//reinit choice variables
						int map_cmd;
						char editExisting;
						int choice;

						// restart loop
						cout << "\nWhat would you like to do? (enter number)" << endl;
						cout << "1. Start/End game" << endl;
						cout << "2. Create/Edit Map" << endl;
						cout << "3. Create/Edit Character" << endl;
						cout << "4. Create/Edit Item" << endl;
						cout << "5. Exit program" << endl;
						int cmd;
						cin >> cmd;
						break;

					}
					else{
						cout << "Enter map width: " << endl;
						cin >> editorWidth;

						cout << "Enter map height: " << endl;
						cin >> editorHeight;
						
						Editor editor = Editor(editorWidth, editorHeight);				
						editor.initEditor();
						vector<int> newMap(editor.editorLoop());
						editor.close();

						cout << "\n[Your new map was created]" << endl;				
						for (int i = 0; i < newMap.size(); i++){
							if (i % editorWidth == 0) cout << endl;
							cout << newMap[i] << " ";
						}

						cout << "\nWould you like to save the map?(y/n)";
						char saveMap;
						cin >> saveMap;

						//saveing map to disk
						if (saveMap == 'y'){
							
							int id = 1;
							CMarkup xml;
							char di[20];
							sprintf_s(di, 20, "maps/%d.xml", id);

							cout << "current map ids:\n";
							while (xml.Load(di))
							{
								cout << id << " ";
								id++;
								sprintf_s(di, 20, "maps/%d.xml", id);
							}
							
							//initialize map object to save map
							Map* mapToDisk = new Map(id,editorWidth,editorHeight);
							
							//convert map vector to xml and save to disk
							mapToDisk->inputMap(newMap);										
						}

						//reinit choice variables
						int map_cmd;
						char editExisting;
						
						// restart loop
						cout << "\nWhat would you like to do? (enter number)" << endl;
						cout << "1. Start/End game" << endl;
						cout << "2. Create/Edit Map" << endl;
						cout << "3. Create/Edit Character" << endl;
						cout << "4. Create/Edit Item" << endl;
						cout << "5. Exit program" << endl;
						int cmd;
						cin >> cmd;
						break;
					}
				default:{
					cout << "exiting program";
					cmd = 5;
				}
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
				cout << "Welcome to the item editor." << endl;
				cout << "what would you like to do?" << endl;
				cout << "1. create new item" << endl;
				cout << "2. edit existing item" << endl;
				cout << "3. exit editor" << endl;
				int item_cmd;

				cin >> item_cmd;

				Item* item = nullptr;

				switch (item_cmd)
				{
				case 1: // create new item
				{
					string type;
					do
					{
						cout << "Enter the type of item you would like to create. "
							<< "\nhelmet, armor, shield, ring, belt, boots, weapon:  " << endl;
						cin >> type;
					} while (type != TYPE_HELMET && type != TYPE_RING && type != TYPE_BOOTS && type != TYPE_ARMOR && type != TYPE_SHIELD &&
						type != TYPE_BELT && type != TYPE_WEAPON);

					int id = 1;
					CMarkup xml;
					char di[20];
					sprintf_s(di, 20, "maps/%d.xml", id);
					while (xml.Load(string(di)))
					{
						id++;
						sprintf_s(di, 20, "items/%d.xml", id);
					}
					cout << "Created new item with ID: " << id << endl;
					item = new Item(id, type, vector<Enhancement>()); //without enhancements.
					break;
				}
				case 2: //edit existing item
				{
					int id;
					do
					{
						cout << "Enter the id of the item you would like to edit: ";
						cin >> id;
						item = Item::load(id);
					} while (item == nullptr);
					break;
				}
				case 3: //exit item editor
				{
					itemedit = false;
					break;
				}
				default:
				{
					cout << "Unknown command." << endl;
				}
				}

				if (item != nullptr)
				{
					bool editItem = true;
					while (editItem)
					{
						cout << "What would you like to do with the item?" << endl;
						cout << "1. Change type" << endl;
						cout << "2. Add enhancement" << endl;
						cout << "3. Remove enhancement of certain type" << endl;
						cout << "4. Exit and Save" << endl;
						cout << "5. Exit and don't save" << endl;
						int editItemCMD;
						cin >> editItemCMD;

						switch (editItemCMD)
						{
						case 1: //Change type 
						{
							string itemType;
							do
							{
								cout << "Enter the type of item you would like to create. "
									<< "\nhelmet, armor, shield, ring, belt, boots, weapon:  " << endl;
								cin >> itemType;
							} while (itemType != TYPE_HELMET && itemType != TYPE_RING && itemType != TYPE_BOOTS && itemType != TYPE_ARMOR
								&& itemType != TYPE_SHIELD && itemType != TYPE_BELT && itemType != TYPE_WEAPON);
							break;
						}
						case 2: //add enhancement
						{
							string enhancement_type;
							int bonus;
							do
							{
								cout << "Enter the type of enhancement you would like to add. "
									<< "\nstrength, constitution, wisdom, charisma, dexterity, intelligence, attackbonus, damagebonus, armorclass: " << endl;
								cin >> enhancement_type;
							} while (enhancement_type != EN_STRENGTH && enhancement_type != EN_CONSTITUTION && enhancement_type != EN_WISDOM
								&& enhancement_type != EN_CHARISMA && enhancement_type != EN_DEXTERITY && enhancement_type != EN_ATTACK_BONUS 
								&& enhancement_type != EN_DAMAGE_BONUS && enhancement_type != EN_ARMOR_CLASS && enhancement_type != EN_INTELLIGENCE);

							do
							{
								cout << "Enter the bonus of the enhancement you would like to add (1 or 5): ";
								cin >> bonus;
							} while (bonus != 1 && bonus != 5);

							item->addEnhancement(Enhancement(enhancement_type, bonus));
							break;
						}
						case 3: //Remove
						{
							string enhancement_type;
							int bonus;

							do
							{
								cout << "Enter the type of enhancement you would like to remove: "
									<< "\nstrength, constitution, wisdom, charisma, dexterity, intelligence, attackbonus, damagebonus, armorclass: " << endl;
								cin >> enhancement_type;
							} while (enhancement_type != EN_STRENGTH && enhancement_type != EN_CONSTITUTION && enhancement_type != EN_WISDOM
								&& enhancement_type != EN_CHARISMA
								&& enhancement_type != EN_DEXTERITY && enhancement_type != EN_ATTACK_BONUS && enhancement_type != EN_DAMAGE_BONUS
								&& enhancement_type != EN_ARMOR_CLASS && enhancement_type != EN_INTELLIGENCE);

							item->removeEnhancement(enhancement_type);
							break;
						}
						case 4: //exit and save 
							if (item->validateItem())
							{
								item->saveItem();
								cout << "\nItem saved" << endl;
							}
							else
							{
								cout << "\nThis item is invalid! These are valid enhancements:" 
									<< "\nHelmet (intelligence, wisdom, armorclass)"
									<< "\nArmor (armorclass)"
									<< "\nShield (armorclass)"
									<< "\nRing (strength, constitution, wisdom, charisma, armorclass)"
									<< "\nBelt (constitution, strength)"
									<< "\nBoots (dexterity, armorclass)"
									<< "\nWeapon (attackbonus, damagebonus)\n"
									<< endl;
								break;
							}
						case 5: //exit don't save
						{
							editItem = false;
						}
						}
					}
				}
			}

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