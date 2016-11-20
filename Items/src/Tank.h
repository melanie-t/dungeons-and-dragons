//! file Tank.h
//! @brief Header file and Implementation of the Tank Character
//!
#pragma once
#include "CharacterBuilder.h"
#include <algorithm>
//! Class for the Tank, inherit from the CharacterBuilder
class Tank : public CharacterBuilder{
public:
	Dice dice;
	//! Method to set the ability scores to the character
	virtual void buildAbilityScores(){
		int abilityScores[6];
		for (int i = 0; i < 6; i++){
			abilityScores[i] = dice.roll("4d6[0]");
		}
		//Sorting the ability Scores
		sort(abilityScores, abilityScores + 6);

		//Assigns the ability score depending on importance
		m_character->setCON(abilityScores[0]);
		m_character->setDEX(abilityScores[1]);
		m_character->setSTR(abilityScores[2]);
		m_character->setINTEL(abilityScores[3]);
		m_character->setCHA(abilityScores[4]);
		m_character->setWIS(abilityScores[5]);
	}
};
