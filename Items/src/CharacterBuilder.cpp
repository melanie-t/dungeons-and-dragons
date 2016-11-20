//! @file CharacterBuilder.cpp
//! @brief Implementation file for the CharacterBuilder
//!
#include "CharacterBuilder.h"

//! method to get the built Character from the builder
//! @return : Character* type of the characterBuilder
Character* CharacterBuilder::getCharacter(){
	return m_character;
}

//! method to build generic Empty Character
void CharacterBuilder::createNewCharacter(){
	m_character = new Character;
}

