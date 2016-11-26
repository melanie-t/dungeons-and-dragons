#pragma once
#include "Observer.h"
#include "Character.h"

class SubjectCharacter : public Observer {
public:
	SubjectCharacter();
	SubjectCharacter(Character* c);
	~SubjectCharacter();
	void Update();
	void logCharacter();

private:
	Character *subject;
	bool showLog = true;
};
