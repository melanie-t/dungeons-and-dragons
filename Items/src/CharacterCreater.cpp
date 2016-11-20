//! @file CharacterCreater.cpp
//! @brief Implementation file for the CharacterCreater Class
//!
#include "CharacterCreater.h"

//! setter method that links the director with the Correct ChracterBuilder
//! @param cb : CharacterBuilder* representing the correct character to build
void CharacterCreater::setCharacterBuild(CharacterBuilder* cb){
	m_characterBuilder = cb;
}

//! getter method that returns the character built by the director
//! @return : Character* of the character built
Character* CharacterCreater::getCharacter(){
	return m_characterBuilder->getCharacter();
}

//! method to instantiate and initialize the correct abilityScore of a character
void CharacterCreater::constructCharacter(){
	m_characterBuilder->createNewCharacter();
	m_characterBuilder->buildAbilityScores();
}
