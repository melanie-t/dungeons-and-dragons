#include "MapBuilder.h"

class FileMapBuilder : public MapBuilder
{
public:
	FileMapBuilder();
	FileMapBuilder(Character* player);
	~FileMapBuilder();
	virtual bool loadMap(int id);
private:
	Character* player;
};