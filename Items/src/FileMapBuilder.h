#include "MapBuilder.h"

class FileMapBuilder : public MapBuilder
{
public:
	FileMapBuilder();
	FileMapBuilder(Character* character);
	~FileMapBuilder();
	virtual void loadMap(int id);
private:
	Character* character;
};