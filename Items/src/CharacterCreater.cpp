#include "CharacterCreater.h"

void CharacterCreater::setCharacterBuild(CharacterBuilder* cb){
	m_characterBuilder = cb;
}

Character* CharacterCreater::getCharacter(){
	return m_characterBuilder->getCharacter();
}

void CharacterCreater::constructCharacter(){
	m_characterBuilder->createNewCharacter();
	m_characterBuilder->buildAbilityScores();
}
