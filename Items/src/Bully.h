//! file Bully.h
//! @brief Header file and Implementation of the Bully Character
//!
#pragma once
#include "CharacterBuilder.h"
#include <algorithm>
//! Class for the Bully, inherit from the CharacterBuilder
class Bully : public CharacterBuilder
{
public:
	//! Method to set the ability scores to the character
	virtual void buildAbilityScores()
	{
		Dice dice;
		int abilityScores[6];
		for (int i = 0; i < 6; i++)
		{
			abilityScores[i] = dice.roll("4d6[0]");
		}
		//Sorting the ability Scores
		sort(abilityScores, abilityScores + 6);

		//Assigns the ability score depending on importance
		m_character->setSTR(abilityScores[0]);
		m_character->setCON(abilityScores[1]);
		m_character->setDEX(abilityScores[2]);
		m_character->setINTEL(abilityScores[3]);
		m_character->setCHA(abilityScores[4]);
		m_character->setWIS(abilityScores[5]);

		//Assigns the charclass
		m_character->setCharClass(1);
	}
};
