#pragma once
#include "Character.h"
#include "Dice.h"

//Abstract class providing the structure for all concrete Character Builders
class CharacterBuilder
{
public:
	//Get the built Character from the builder
	Character* getCharacter();
	//Build generic Empty Character
	void createNewCharacter();
	//Generates the Ability Score according to subtypes
	virtual void buildAbilityScores() = 0;


protected:
	//Product built by character Builder
	Character* m_character;
};

