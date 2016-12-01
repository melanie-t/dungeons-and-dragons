//! @file GameObjectLogger.h
//! @brief Header file for GameObjectLogger Class
//!
#pragma 

#include <string>
using namespace std;

class GameObjectLogger
{
public:
	GameObjectLogger();
	void UpdateSetup(int id);
	void UpdateMap(int id);
	void UpdateTurn(string character);
	void UpdateEnd(bool won = true);
	void toggle();

	static GameObjectLogger* getInstance();

private:
	bool showLog;

	static GameObjectLogger* instance;
};
