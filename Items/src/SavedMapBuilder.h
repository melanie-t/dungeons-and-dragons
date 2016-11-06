#include "MapBuilder.h"

class SavedMapBuilder : public MapBuilder
{
public:
	virtual bool loadMap(int);
};