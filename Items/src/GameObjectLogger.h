#pragma 

#include <string>
using namespace std;

class GameObjectLogger
{
public:
	GameObjectLogger();
	void UpdateSetup();
	void UpdateMap();
	void UpdateTurn(string character);
	void UpdateEnd();
	void toggle();

	static GameObjectLogger* getInstance();

private:
	bool showLog;

	static GameObjectLogger* instance;
};
