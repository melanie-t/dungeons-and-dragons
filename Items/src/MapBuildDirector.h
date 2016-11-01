#include "MapBuilder.h"

class MapBuildDirector //Temporary name
{
public:
	Map* getMap(){ mapBuilder->getMap(); }

	void setMapBuilder(MapBuilder* mapBuilder);
	void constructMap();
private:
	MapBuilder* mapBuilder;

};