/** @file Character.h
* @brief Header file for the Character class  
* @author Melanie Taing
* @date 10/21/2016
* 
* Character creation in Dungeons and Dragons follows these rules: 
*	1. Ability scores generated through 4d6 dice (Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma)
*	2. Ability scores range from 3 to 18
*	3. Ability modifiers are calculated as (abilityScore-10)/2
*	4. Secondary stats are calculated using ability modifiers (armor class, hit points, attack bonus, damage bonus)
*		4a. Armor Class is calculated as the 10 + armor bonus + shield bonus + Dexterity modifier
*		4b. Hit Points are calculated at level 1 as 10 + Constitution modifier. Any level after that is 1d10 + Constitution Modifier
*		4c. Attack Bonus (AB) increases as characters level up (+1, +2, +3, +4, +5, etc.)
*			see http://www.dandwiki.com/wiki/SRD:Fighter
*		4d. Number of Attacks increase every 5 levels (LV 1-5: 1 ATT. LV 6-10: 2 ATT., etc.)
*		4e. Damage Bonus is calculated as the Strength Modifier
*	5. Ability to equip items
* 
* In order to generate random ability scores, I used the rand() and srand() function from <stdlib.h> coupled with time from <time.h>.
* The function srand ensures that the seed is random (corresponds with time, so it's constantly changing).
* To stay within the allowed range of ability scores (3-18), I shifted rand() (with mod and addition operations) to fit the allowed range.
*
* The libraries used are:
*	1. Standard Input/Output Streams Library <iostream> is necessary to display the stats of the character created, by using cout
*	2. C++ Standard Library <stdlib.h> is necessary to randomly generate ability scores, by using rand() and srand()
*	3. Time Library <time.h> is necessary to ensure seed randomization so it doesn't generate the same numbers, by using time
*/

#pragma once

#include "GameObject.h"
#include "Observable.h"
#include "ItemContainer.h"
#include "AbilityModifierTypes.h"
#include "CharacterEquipEnum.h"
#include "Strategy.h"
#include "CharacterSpriteTypes.h"
#include "PlayerActionTypes.h"
#include <string>

using namespace std;

//! Class that implements a character 
class Character : public Observable
{
public:
	Character();
	Character(int lvl, int str, int dex, int con, int intel, int wis, int cha);
	Character(string name, int charclass, int lvl, int str, int dex, int con, int intel, int wis,
		int cha, int hp, ItemContainer backpack, Item equips[7]);

	void notify();
	void attach(Character* c);
	void detach(Character* c);

	void initSprite(CharacterSpriteType type);

	bool validateNewCharacter();
	void statGenerator();
	int abilityModifier(int abilityScore);
	void secondaryStatCalc();
	void hit(int damage);
	int getHitPoints();
	void setHitPoints(int HP);
	int getLevel();
	void setLevel(int level);
	int getArmorClass();
	void setArmorClass(int armorClass);
	int getAttackBonus();
	void setAttackBonus(int attackBonus);
	int getDamageBonus();
	void setDamageBonus(int damageBonus);
	int getSTR();
	void setSTR(int STR);
	int getDEX();
	void setDEX(int DEX);
	int getCON();
	void setCON(int CON);
	int getINTEL();
	void setINTEL(int INTEL);
	int getWIS();
	void setWIS(int WIS);
	int getCHA();
	void setCHA(int CHA);
	string getName();
	void setName(string newName);
	int getCharClass();
	void setCharClass(int classOfChar);
	void levelUp();

	void displayStats();
	string statString();
	string classtoString();
	void saveCharacter();
	static Character* loadCharacter(string name);

	//Methods for Item
	ItemContainer getBackpack();
	void setEquips(Item equips[7]);
	Item* getEquip(string type);
	void equip(Item* item);
	void unequip(Item* item);
	void setEnh(string type, int bonus);
	void initEnh();

	//Methods for Strategy
	bool isHoldingWeapon(){ return this->weaponEquipped; }
	Strategy* getStrategy();
	void setStrategy(Strategy* strat);
	pos getPosition();
	void setPosition(int x, int y);
	void move(PlayerMove move);
	void changeSprite(PlayerMove move);
	sf::Sprite* getSprite() { return this->characterSprite; }
	int attackRoll(int d20);
	int attack(int attackRoll);
	string getCharacterType();


private:
	int abilityScores[6];
	int currentHitPoints;
	int level;
	int armorClass;
	int attackBonus;
	int damageBonus;
	int charClass;
	bool gameover = false;
	
	bool helmetEquipped = false,
		armorEquipped = false,
		beltEquipped = false,
		bootsEquipped = false,
		shieldEquipped = false,
		weaponEquipped = false,
		ringEquipped = false;

	ItemContainer backpack;
	Item equips[7]; //(0)helmet, (1)armor, (2)belt, (3)boots, (4)shield, (5)weapon, (6)ring
	string name;
	string gender;
	Character* List[10];
	Strategy* strategy;
	pos position;
	string characterType;

	sf::Texture* characterTexture;
	sf::Sprite* characterSprite;

protected:
	int enh_str, enh_dex, enh_con, enh_int, enh_wis, enh_cha, enh_armorclass, enh_damagebonus, enh_attackbonus;
};

