#pragma once
#include "Observer.h"
#include "Dice.h"

class SubjectDice : public Observer {
public:
	SubjectDice();
	SubjectDice(Dice* d);
	~SubjectDice();
	void Update();
	void Add(Dice* d);
	void logDice();

private:
	Dice *subject;
	bool showLog = true;
};
