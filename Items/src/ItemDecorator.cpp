#include <iostream>
#include "ItemDecorator.h"
using std::cout;

//! Default constructor that intializes decoratedCharacter and equip to nullptr
ItemDecorator::ItemDecorator()
{
	this->decoratedCharacter = nullptr;
	this->equip = nullptr;
}

//! Constructor that initializes ItemDecorated to the Character pointer passed as a parameter
//! @param decorator : Pointer to Character
ItemDecorator::ItemDecorator(Character *decorator) {
	this->decoratedCharacter = decorator;
}

//! Implementation of a getter method for strength
//! @return int: value of decoratedCharacter's strength
int ItemDecorator::getSTR() { 
	return decoratedCharacter->getSTR(); 
}

//! Implementation of a getter method for constitution
//! @return int: value of decoratedCharacter's constitution
int ItemDecorator::getCON() {
	return decoratedCharacter->getCON();
}

//! Implementation of a getter method for dexterity
//! @return int: value of decoratedCharacter's dexterity
int ItemDecorator::getDEX() {
	return decoratedCharacter->getDEX();
}

//! Implementation of a getter method for wisdom
//! @return int: value of decoratedCharacter's wisdom
int ItemDecorator::getWIS() {
	return decoratedCharacter->getWIS();
}

//! Implementation of a getter method for intelligence
//! @return int: value of decoratedCharacter's intelligence
int ItemDecorator::getINTEL() {
	return decoratedCharacter->getINTEL();
}

//! Implementation of a getter method for charisma
//! @return int: value of decoratedCharacter's charisma
int ItemDecorator::getCHA() {
	return decoratedCharacter->getCHA();
}

//! Implementation of a getter method for armorclass
//! @return int: value of decoratedCharacter's armorclass
int ItemDecorator::getArmorClass(){
	return decoratedCharacter->getArmorClass();
}

//! Implementation of a getter method for attackbonus
//! @return int: value of decoratedCharacter's attackbonus
int ItemDecorator::getAttackBonus(){
	return decoratedCharacter->getAttackBonus();
}

//! Implementation of a getter method for damagebonus
//! @return int: value of decoratedCharacter's damagebonus
int ItemDecorator::getDamageBonus(){
	return decoratedCharacter->getDamageBonus();
}

//! wear function
//! equips the item to the object at the pointer passed as a parameter
//! @param item : item that is going to be worn
void ItemDecorator::wear(Item* item) 
{
	// Item not equipped
	if (!itemEquipped(item))
	{
		decoratedCharacter->equip(item);
		setEquipTF(item, true);
		update(item, true);
	}

	// Item already equipped
	else
	{
		//Puts current item into backpack
		update(item, false);
		cout << "\n------------------------------------------------" << endl;
		cout << item->getType() << " swapped !" << endl;
		cout << "------------------------------------------------" << endl;
		decoratedCharacter->unequip(item);

		decoratedCharacter->equip(item);
		update(item, true);
	}
}

//! itemEquipped function
//! checks if the item type passed as a parameter is already equipped
//! @param item : item that is being checked if it's already worn
//! @return true if it is already equipped, false otherwise
bool ItemDecorator::itemEquipped(Item* item)
{
	string type = item->getType();
	if (type == TYPE_HELMET)
		return helmetEquipped;

	else if (type == TYPE_SHIELD)
		return shieldEquipped;

	else if (type == TYPE_RING)
		return ringEquipped;

	else if (type == TYPE_ARMOR)
		return armorEquipped;

	else if (type == TYPE_BELT)
		return beltEquipped;

	else if (type == TYPE_BOOTS)
		return bootsEquipped;

	else if (type == TYPE_WEAPON)
		return weaponEquipped;
}

//! setEquipTF function
//! sets the item's itemEquipped value as true or false, depending on parameter
//! @param item : item that is being modified
//! @param boolean : true represents the item as equipped and false represents the item as unequipped
void ItemDecorator::setEquipTF(Item* item, bool boolean)
{
	string type = item->getType();
	if (type == TYPE_HELMET)
		helmetEquipped = boolean;

	else if (type == TYPE_SHIELD)
		shieldEquipped = boolean;

	else if (type == TYPE_RING)
		ringEquipped = boolean;

	else if (type == TYPE_ARMOR)
		armorEquipped = boolean;

	else if (type == TYPE_BELT)
		beltEquipped = boolean;

	else if (type == TYPE_BOOTS)
		bootsEquipped = boolean;

	else if (type == TYPE_WEAPON)
		weaponEquipped = boolean;
}

//! remove function
//! unequips the item passed as a parameter
//! @param item : item that will be unequiped
void ItemDecorator::remove(Item* item)
{
	// Item equipped
	if (itemEquipped(item))
	{
		cout << "\n------------------------------------------------" << endl;
		cout << item->getType() << " removed !" << endl;
		cout << "------------------------------------------------" << endl;
		update(item, false);
		decoratedCharacter->unequip(item);
		setEquipTF(item, false);
	}
}

//! removeEnh function
//! removes the enhancement type passed as a parameter
//! @param enh : string type of enhancement being removed
void ItemDecorator::removeEnh(string enh)
{
	decoratedCharacter->setEnh(enh, -(equip->getEnhancement(enh)));
}

//! update function
//! updates the enhancement/ability modifier bonus depending on parameters passed
//! if statUpdate is true, then it will add the stats, and subtract if false
//! @param item : item being equipped/unequipped
//! @param statUpdate : true if item is being equipped, false if item is being unequipped
void ItemDecorator::update(Item* item, bool statUpdate)
{
	equip = decoratedCharacter->getEquip(item->getType());

	// Equip added: update stats
	if (statUpdate)
	{
		decoratedCharacter->setEnh("strength", equip->getEnhancement("strength"));
		decoratedCharacter->setEnh("constitution", equip->getEnhancement("constitution"));
		decoratedCharacter->setEnh("dexterity", equip->getEnhancement("dexterity"));
		decoratedCharacter->setEnh("intelligence", equip->getEnhancement("intelligence"));
		decoratedCharacter->setEnh("wisdom", equip->getEnhancement("wisdom"));
		decoratedCharacter->setEnh("charisma", equip->getEnhancement("charisma"));
		decoratedCharacter->setEnh("attackbonus", equip->getEnhancement("attackbonus"));
		decoratedCharacter->setEnh("damagebonus", equip->getEnhancement("damagebonus"));
		decoratedCharacter->setEnh("armorclass", equip->getEnhancement("armorclass"));
	}

	// Equip removed: substract stats
	else
	{
		decoratedCharacter->setEnh("strength", -(equip->getEnhancement("strength")));
		decoratedCharacter->setEnh("constitution", -(equip->getEnhancement("constitution")));
		decoratedCharacter->setEnh("dexterity", -(equip->getEnhancement("dexterity")));
		decoratedCharacter->setEnh("intelligence", -(equip->getEnhancement("intelligence")));
		decoratedCharacter->setEnh("wisdom", -(equip->getEnhancement("wisdom")));
		decoratedCharacter->setEnh("charisma", -(equip->getEnhancement("charisma")));
		decoratedCharacter->setEnh("attackbonus", -(equip->getEnhancement("attackbonus")));
		decoratedCharacter->setEnh("damagebonus", -(equip->getEnhancement("damagebonus")));
		decoratedCharacter->setEnh("armorclass", -(equip->getEnhancement("armorclass")));
	}
}