#include <map>

#include "Campaign.h"
#include "FileMapBuilder.h"
#include "StatisticsHelper.h"
#include "Door.h"

Campaign::Campaign(Map* start)
{
	this->begin = start;
	this->setupCampaign();
}
void Campaign::setupCampaign()
{
	this->setup(begin);
}
void Campaign::setup(Map* map)
{
	std::vector<pos> doors = map->getDoors();

	for (std::vector<pos>::iterator doorpos = doors.begin(); doorpos != doors.end(); ++doorpos)
	{
		Door* door = static_cast<Door*>(map->getObject(doorpos->x, doorpos->y));
		if (door->getStart()) continue; // skip start doors

		cout << "Door Detected at (" << doorpos->x << ", " << doorpos->y << ")" << "on map #" << map->getID() << endl;
		cout << "Pick a map to link to this door below" << Statistics::getInstance()->getNumMaps() << ". Enter 0 to make the door a finish line.";
		int mapid;

		do
		{
			cin >> mapid;

		} while (mapid > Statistics::getInstance()->getNumMaps() || mapid < 0);

		if (mapid == 0) continue;
		else
		{
			FileMapBuilder builder(map->getPlayer());
			builder.loadMap(mapid);
			Map* map = builder.getMap();
			door->setDestination(map);
			setup(map);
		}
	}
}
Campaign* Campaign::createCampaign()
{
	cout << "Pick a Starting map ID below" << Statistics::getInstance()->getNumMaps() << " and above 0; ";
	int start;

	do
	{
		cin >> start;

	} while (start > Statistics::getInstance()->getNumMaps() || start <= 0);

	//Load the map that the campaign will start on.
	FileMapBuilder builder;
	builder.loadMap(start);

	Map* startMap = builder.getMap();
	
	return new Campaign(startMap);
}