#include <iostream>
#include "ItemDecorator.h"
using std::cout;

ItemDecorator::ItemDecorator()
{
	this->decoratedCharacter = nullptr;
	this->equip = nullptr;
}

ItemDecorator::ItemDecorator(Character *decorator) {
	this->decoratedCharacter = decorator;
}

int ItemDecorator::getSTR() { 
	return decoratedCharacter->getSTR(); 
}

int ItemDecorator::getCON() {
	return decoratedCharacter->getCON();
}

int ItemDecorator::getDEX() {
	return decoratedCharacter->getDEX();
}

int ItemDecorator::getWIS() {
	return decoratedCharacter->getWIS();
}

int ItemDecorator::getINTEL() {
	return decoratedCharacter->getINTEL();
}

int ItemDecorator::getCHA() {
	return decoratedCharacter->getCHA();
}

int ItemDecorator::getArmorClass(){
	return decoratedCharacter->getArmorClass();
}

int ItemDecorator::getAttackBonus(){
	return decoratedCharacter->getAttackBonus();
}

int ItemDecorator::getDamageBonus(){
	return decoratedCharacter->getDamageBonus();
}

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


void ItemDecorator::removeEnh(string enh)
{
	decoratedCharacter->setEnh(enh, -(equip->getEnhancement(enh)));
}

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