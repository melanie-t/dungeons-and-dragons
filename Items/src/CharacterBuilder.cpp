#include "CharacterBuilder.h"

//Get the built Character from the builder
Character* CharacterBuilder::getCharacter(){
	return m_character;
}

//Build generic Empty Character
void CharacterBuilder::createNewCharacter(){
	m_character = new Character;
}

