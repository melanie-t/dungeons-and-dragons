//! @file ItemDecorator.h 
//! @brief Header file for the ItemDecorator class  
//!

#pragma once
#include "Character.h"
#include "Item.h"

// Class that implements Decorator pattern for equipping items in Characters
class ItemDecorator : public Character {

protected:
	Character* decoratedCharacter;
	Item* equip;

public:
	ItemDecorator();
	ItemDecorator(Character *decoratedCharacter);

	int getSTR();
	int getCON();
	int getDEX();
	int getWIS();
	int getINTEL();
	int getCHA();
	int getArmorClass();
	int getAttackBonus();
	int getDamageBonus();

	void wear(Item* item);
	bool itemEquipped(Item* item);
	void setEquipTF(Item* item, bool boolean);
	void remove(Item* item);
	void removeEnh(string enh);
	void update(Item* item, bool statUpdate);

protected:
	bool helmetEquipped = false,
		armorEquipped = false,
		beltEquipped = false,
		bootsEquipped = false,
		shieldEquipped = false,
		weaponEquipped = false,
		ringEquipped = false;

	Item Equips[7];
};