//! @file 
//! @brief Implementation file for the MapBuildDirector class  
//!
#include "MapBuildDirector.h"

//! getMap function
//! @return returns the loaded map.
Map* MapBuildDirector::getMap()
{
	return this->mapBuilder->getMap();
}
//! setMapBuilder function
//! sets the map builder to use. So we cans witch between FileMapBuilder and SavedMapBuilder
void MapBuildDirector::setMapBuilder(MapBuilder* mapBuilder)
{
	this->mapBuilder = mapBuilder;
}

//! constructMap function
//! parses a map with the specified id.
//! @param id the id of the map to parse
Map* MapBuildDirector::constructMap(int id)
{
	this->mapBuilder->loadMap(id);
	return getMap();
}