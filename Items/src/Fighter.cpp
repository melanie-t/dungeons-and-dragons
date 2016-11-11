//! @file 
//! @brief Implementation file for the Fighter class  
//!
#include "Character.h"
#include "Fighter.h"
#include "Markup.h"
#include <iostream> /* cout */

using std::cout;
using std::endl;

//! Constructor: Passes values to each ability score
Fighter::Fighter(int level, int str, int dex, int con, int intel, int wis, int cha):
													Character(level, str, dex, con, intel, wis, cha)
{
	setCharClass(1);
}

//! Constructor: For loading Fighters
Fighter::Fighter(int level, int str, int dex, int con, int intel, int wis, int cha, string name)
{
	setCharClass(1);
	setLevel(level);
	setSTR(str);
	setDEX(dex);
	setCON(con);
	setINTEL(intel);
	setWIS(wis);
	setCHA(cha);
	setName(name);
}

//! Default constructor: Assigns values for level 1
Fighter::Fighter()
{
	setLevel(1);
	setName("Unknown");
	setCharClass(1);
}

//! Constructor for Fighter
//! @param level level of fighter
Fighter::Fighter(string name)
{
	setName(name);
	setLevel(1);
	setCharClass(1);
	statGenerator();
}

//! validateNewFighter function
//! @brief validates the stats of the created Fighter.
bool Fighter::validateNewFighter()
{
	validateNewCharacter();
	if (getHitPoints() < 10)
		return false;
	if (getArmorClass() < 0)
		return false;
	if (getAttackBonus() < 0)
		return false;
	if (getDamageBonus() < 0)
		return false;
	return true;
}

Fighter* Fighter::loadFighter(string name)
{
	CMarkup xml;
	if (xml.Load("characters/" + name + ".xml"))
	{
		xml.FindElem();
		if (xml.GetTagName() != "character")
		{
			cout << "This file is not a character." << endl;
			cout << xml.GetTagName() << endl;
		}
		else
		{
			xml.IntoElem();
			int level, str, dex, con, intel, wis, cha;
			while (xml.FindElem())
			{
				string tag = xml.GetTagName();
				if (tag == "level")
				{
					level = atoi(xml.GetData().c_str());
				}
				else if (tag == "strength")
				{
					str = atoi(xml.GetData().c_str());
				}
				else if (tag == "dexterity")
				{
					dex = atoi(xml.GetData().c_str());
				}
				else if (tag == "constitution")
				{
					con = atoi(xml.GetData().c_str());
				}
				else if (tag == "intelligence")
				{
					intel = atoi(xml.GetData().c_str());
				}
				else if (tag == "wisdom")
				{
					wis = atoi(xml.GetData().c_str());
				}
				else if (tag == "charisma")
				{
					cha = atoi(xml.GetData().c_str());
				}
			}
			return new Fighter(level, str, dex, con, intel, wis, cha, name);
		}
	}
	return NULL; //Empty
}


