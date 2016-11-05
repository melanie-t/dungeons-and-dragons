#include "Map.h"
#include "Character.h"

class MapBuilder
{
protected:
	Map* m_Map;
public:
	Map* getMap(){ return this->m_Map; }

	void createNewMap(){ this->m_Map = new Map(); };

	virtual void loadMap(int id) = 0;
};