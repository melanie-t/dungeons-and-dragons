#include <thread>
#include <Windows.h>

//CharacterBuilder (Bully Fighter, Nimble Fighter, Tank Fighter)
//#include "CharacterCreater.h"
//#include "Bully.h"
//#include "Tank.h"
//#include "Nimble.h"
#include "Game.h"
#include "FileMapBuilder.h"
#include "SavedMapBuilder.h"
#include "Character.h"
#include "Fighter.h"
#include "Enemy.h"
#include "Door.h"
#include "Item.h"
#include "Markup.h"
#include "Friend.h"
#include "StatisticsHelper.h"
#include "Campaign.h"
using namespace std;


std::thread runGameThread;
/**
Console input thread.
Take commands through the console. Temp
*/
void runGame(Map* chosenMap)
{
	//Character* character = Character::loadCharacter(characterName);
	//character->setName(characterName);

	//FileMapBuilder builder(character);
	//builder.loadMap(chosenMap);
	//Map* map = builder.getMap();
	//builder.createCampagin(map);

	Game* game = new Game(chosenMap->getWidth(), chosenMap->getLength(), chosenMap);

	try {
		game->go();
	}
	catch (char* e) {
		MessageBoxA(NULL, e, "EXCEPTION OCCURED", MB_OK | MB_ICONERROR);
	}
	runGameThread.detach();
}

inline void toLower(basic_string<char>& s) {
	for (basic_string<char>::iterator p = s.begin(); p != s.end(); ++p) 
	{
		*p = tolower(*p);
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
				std::cout << "Choose a Fighter from the list." << endl;

				vector<string> characters = Statistics::getInstance()->getCharacterList();

				for (int i = 0; i != characters.size(); i++)
				{
					string name = *(characters.begin() + i);
					cout << name << endl;
				}

				cin >> name;

				Character* player = Character::loadCharacter(name);
				Campaign* camp = Campaign::loadCampaign(1, player);//Campaign::createCampaign(player);
				//camp->saveCampaign();

				/*cout << "Choose a map id from the list below:" << endl;

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
				cin >> chosenMap;*/

				gameRunning = true;

				runGameThread = std::thread(runGame, camp->getBeginningMap());
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
				bool created = false;

				switch (map_cmd)
				{
				case 1: // create map:
				{
					created = true;
					int width, length;
					cout << "What length should the map be?" << endl;
					cin >> length;
					cout << "What width should the map be?" << endl;
					cin >> width;
					//map = new Map();

					//find a better way of doing this.
					int id = Statistics::getInstance()->getNumMaps() + 1;
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
						map->printMap();

						cout << "What would you like to do with the map?" << endl;
						cout << "1. Add Door" << endl;
						cout << "2. Add Chest" << endl;
						cout << "3. Add Enemy" << endl;
						cout << "4. Add Friend" << endl;
						cout << "5. Exit & Save" << endl;
						cout << "6. Exit & Don't Save" << endl;
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
							} while (x > map->getWidth() || x < 0 || y > map->getWidth() || y < 0);
						}

						switch (editcmd)
						{
						case 1: //add door.
						{
							//int mapid;
							bool start;
							//cout << "Enter mapid that the door leads to: ";
							//cin >> mapid;
							cout << "Is this a start or end position(1 for start, 0 for end): ";
							cin >> start;
							map->fillCell(x, y, new Door(start));
							break;
						}
						case 2: // add item in this area
						{
							map->fillCell(x, y, new GameObject(OBJ_CHEST));
							break;
						}
						case 3: //add enemy in this area
						{
							map->fillCell(x, y, new Enemy());
							break;
						}
						case 4: //add friend in this area
						{
							map->fillCell(x, y, new Friend());
							break;
						}
						case 5: // exit + save, no break function
						{
							if (!map->saveMap())
							{
								cout << "Invalid map." << endl;
								break;
							}
							else if (created)
							{
								int numMap = Statistics::getInstance()->getNumMaps();
								Statistics::getInstance()->setNumMaps(numMap+1);
							}
						}
						case 6: //exit without saving.
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
					toLower(name);  //will convert to lowercase
					Fighter newFighter(name);
					newFighter.notify();

					//Ask if player wants to save this character
					cout << "Do you want to save this Fighter (Y/N)?" << endl;
					cin >> decision;
					if (decision == 'Y' || decision == 'y')
					{
						newFighter.saveCharacter();
						cout << "Fighter " << name << " saved. Returning to menu.\n" << endl;
						Statistics::getInstance()->addCharacter(name);
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
					toLower(name);

					Character* fighterPointer;
					fighterPointer = Character::loadCharacter(name);

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
				bool created = false;

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

					created = true;
					int id = Statistics::getInstance()->getNumItems() + 1;

					cout << "Created new item with ID: " << id << endl;
					item = new Item(id, type, vector<Enhancement>(), ""); //without enhancements.
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

								if ((item->getType() == TYPE_HELMET && (enhancement_type != EN_INTELLIGENCE && enhancement_type != EN_WISDOM
										&& enhancement_type != EN_ARMOR_CLASS))
									|| ((item->getType() == TYPE_ARMOR || item->getType() == TYPE_SHIELD) && (enhancement_type != EN_ARMOR_CLASS))
									|| ((item->getType() == TYPE_RING) && (enhancement_type != EN_STRENGTH || enhancement_type != EN_CONSTITUTION
										|| enhancement_type != EN_WISDOM || enhancement_type != EN_CHARISMA 
										|| enhancement_type != EN_ARMOR_CLASS))
									|| (item->getType() == TYPE_BOOTS && (enhancement_type != EN_DEXTERITY && enhancement_type != EN_ARMOR_CLASS))
									|| (item->getType() == TYPE_WEAPON && (enhancement_type != EN_ATTACK_BONUS && enhancement_type != EN_DAMAGE_BONUS)))
								{
									cout << "Invalid Enhancement. Valid Enhancements for each item type: "
										<< "\nHelmet (intelligence, wisdom, armorclass)"
										<< "\nArmor (armorclass)"
										<< "\nShield (armorclass)"
										<< "\nRing (strength, constitution, wisdom, charisma, armorclass)"
										<< "\nBelt (constitution, strength)"
										<< "\nBoots (dexterity, armorclass)"
										<< "\nWeapon (attackbonus, damagebonus)\n"
										<< endl;
									enhancement_type = "uyeiug"; //abritrary, just to make this do/while continue to loop.
								}
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
							//int bonus;

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
								int num = Statistics::getInstance()->getNumItems();
								Statistics::getInstance()->setNumItems(num + 1);
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
