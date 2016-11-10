#include "Game.h"
#include "FileMapBuilder.h"
#include "Character.h"
#include <Windows.h>
int main(){
	Character* charater = new Character(1, 1, 1, 1, 1, 1, 13, "james");
	charater->saveCharacter();
	FileMapBuilder builder(charater);
	builder.loadMap(1);
	Map* map = builder.getMap();
	vector<int> out = map->outputMap();

	Game* game = new Game(16, 8, map->outputMap());

	for (int i = 0; i != out.size(); i++)
	{
		cout << out[i] << endl;
	}
	try{
		game->go();
	}
	catch (char* e){
		MessageBoxA(NULL, e, "EXCEPTION OCCURED", MB_OK | MB_ICONERROR);
	}
}