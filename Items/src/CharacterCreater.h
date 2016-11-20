//! @file CharacterCreater.h
//! @brief Header file for the CharacterCreater (Director file)
//!
#pragma once
#include "CharacterBuilder.h"

//Director Class for character builder
class CharacterCreater
{
public:
	// method to link the CharacterBuilder
	void setCharacterBuild(CharacterBuilder* cb);
	// method to return the character built
	Character* getCharacter();
	// method to create the Character with the characterBuilder
	void constructCharacter();

private:
	CharacterBuilder* m_characterBuilder;
};

