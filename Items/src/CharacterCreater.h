#pragma once
#include "CharacterBuilder.h"

//Director Class for character builder
class CharacterCreater
{
public:
	void setCharacterBuild(CharacterBuilder* cb);
	Character* getCharacter();
	void constructCharacter();

private:
	CharacterBuilder* m_characterBuilder;
};

