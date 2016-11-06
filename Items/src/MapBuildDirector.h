//! @file 
//! @brief Header file for the MapBuildDirector class  
//!
#include "MapBuilder.h"

class MapBuildDirector
{
public:
	~MapBuildDirector(){ delete mapBuilder;  }

	Map* getMap();
	
	void setMapBuilder(MapBuilder* mapBuilder);
	Map* constructMap(int id);
private:
	MapBuilder* mapBuilder;

};