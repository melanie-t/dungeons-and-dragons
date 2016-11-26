#pragma once
#include "Observer.h"
#include "Game.h"

class SubjectGame : public Observer {
public:
	SubjectGame();
	SubjectGame(Game* g);
	~SubjectGame();
	void Update();
	void logGame();

private:
	Game *subject;
	bool showLog = true;
};
