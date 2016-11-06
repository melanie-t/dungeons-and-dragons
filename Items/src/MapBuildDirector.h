#include "MapBuilder.h"

class MapBuildDirector //Temporary name
{
public:
	~MapBuildDirector(){ delete mapBuilder;  }

	Map* getMap();
	
	void setMapBuilder(MapBuilder* mapBuilder);
	Map* constructMap(int id);
private:
	MapBuilder* mapBuilder;

};